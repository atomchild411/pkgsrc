/*
 * Playback through IRIX's Audio Library (libaudio, <dmedia/audio.h>): an
 * output port on the default output device, written by the mixer thread.
 *
 * The device's sample rate is the system's, shared by every program
 * playing on it, so the device is mixed at that rate and not changed.
 * Samples are 16-bit, mono or stereo. alWriteFrames blocks until the
 * port's queue has room for a period, which paces the mixer.
 */

#include "config.h"

#include "irixal.h"

#include <algorithm>
#include <atomic>
#include <cerrno>
#include <cstring>
#include <exception>
#include <string>
#include <thread>
#include <vector>

#include "althrd_setname.h"
#include "core/device.h"
#include "core/helpers.h"
#include "gsl/gsl"

#if HAVE_CXXMODULES
import logging;
#else
#include "core/logging.h"
#endif

/* The Audio Library's names share OpenAL's AL_ prefix, and four are
 * defined by both. Its header comes last; nothing below uses OpenAL's. */
#undef AL_CHANNELS
#undef AL_GAIN
#undef AL_INVALID_VALUE
#undef AL_VERSION
#include <dmedia/audio.h>


namespace {

using namespace std::string_view_literals;

[[nodiscard]] constexpr auto GetDefaultName() noexcept { return "IRIX Audio Library"sv; }

/* The last Audio Library error, as text. */
auto ALError() -> const char*
{
    const char *str{alGetErrorString(errno)};
    return str ? str : "unknown error";
}

/* The default output device's sample rate: 0 if it cannot be read. */
auto DeviceRate() -> unsigned
{
    ALpv pv{};
    pv.param = AL_RATE;
    if(alGetParams(AL_DEFAULT_OUTPUT, &pv, 1) < 0 || pv.sizeOut < 0)
        return 0;
    const double rate{alFixedToDouble(pv.value.ll)};
    if(!(rate >= 8000.0 && rate <= 192000.0))
        return 0;
    return static_cast<unsigned>(rate + 0.5);
}


struct IrixALBackend final : BackendBase {
    explicit IrixALBackend(gsl::not_null<DeviceBase*> const device) noexcept : BackendBase{device}
    { }
    ~IrixALBackend() override;

    int mixerProc();

    void open(std::string_view name) override;
    bool reset() override;
    void start() override;
    void stop() override;

    ALport mPort{nullptr};

    std::vector<std::byte> mBuffer;

    std::atomic<bool> mKillNow{true};
    std::thread mThread;
};

IrixALBackend::~IrixALBackend()
{
    if(mPort)
        alClosePort(mPort);
    mPort = nullptr;
}

int IrixALBackend::mixerProc()
{
    SetRTPriority();
    althrd_setname(GetMixerThreadName());

    const auto frame_step = std::size_t{mDevice->channelsFromFmt()};
    const auto update_size = mDevice->mUpdateSize;

    while(!mKillNow.load(std::memory_order_acquire)
        && mDevice->Connected.load(std::memory_order_acquire))
    {
        mDevice->renderSamples(mBuffer.data(), update_size, frame_step);
        if(alWriteFrames(mPort, mBuffer.data(), gsl::narrow_cast<int>(update_size)) < 0)
        {
            ERR("alWriteFrames failed: {}", ALError());
            mDevice->handleDisconnect("Failed to write playback samples: {}", ALError());
            break;
        }
    }

    return 0;
}


void IrixALBackend::open(std::string_view name)
{
    if(name.empty())
        name = GetDefaultName();
    else if(name != GetDefaultName())
        throw al::backend_exception{al::backend_error::NoDevice, "Device name \"{}\" not found",
            name};

    if(DeviceRate() == 0)
        throw al::backend_exception{al::backend_error::NoDevice,
            "No default audio output: {}", ALError()};

    mDeviceName = name;
}

bool IrixALBackend::reset()
{
    if(mPort)
        alClosePort(mPort);
    mPort = nullptr;

    if(const auto rate = DeviceRate())
        mDevice->mSampleRate = rate;

    if(mDevice->FmtChans != DevFmtMono)
        mDevice->FmtChans = DevFmtStereo;
    mDevice->FmtType = DevFmtShort;

    /* The port's queue holds the whole buffer, at least two periods. */
    mDevice->mBufferSize = std::max(mDevice->mBufferSize, mDevice->mUpdateSize*2u);
    const auto channels = int{gsl::narrow_cast<int>(mDevice->channelsFromFmt())};

    ALconfig config{alNewConfig()};
    if(!config)
    {
        ERR("alNewConfig failed: {}", ALError());
        return false;
    }
    if(alSetSampFmt(config, AL_SAMPFMT_TWOSCOMP) < 0
        || alSetWidth(config, AL_SAMPLE_16) < 0
        || alSetChannels(config, channels) < 0
        || alSetQueueSize(config, gsl::narrow_cast<int>(mDevice->mBufferSize)) < 0)
    {
        ERR("Could not configure the port: {}", ALError());
        alFreeConfig(config);
        return false;
    }
    mPort = alOpenPort("OpenAL Soft", "w", config);
    alFreeConfig(config);
    if(!mPort)
    {
        ERR("alOpenPort failed: {}", ALError());
        return false;
    }

    setDefaultChannelOrder();

    mBuffer.resize(std::size_t{mDevice->mUpdateSize} * mDevice->frameSizeFromFmt());
    std::ranges::fill(mBuffer, std::byte{});

    return true;
}

void IrixALBackend::start()
{
    try {
        mKillNow.store(false, std::memory_order_release);
        mThread = std::thread{&IrixALBackend::mixerProc, this};
    }
    catch(std::exception& e) {
        throw al::backend_exception{al::backend_error::DeviceError,
            "Failed to start mixing thread: {}", e.what()};
    }
}

void IrixALBackend::stop()
{
    if(mKillNow.exchange(true, std::memory_order_acq_rel) || !mThread.joinable())
        return;
    mThread.join();
}

} // namespace

auto IrixALBackendFactory::getFactory() -> BackendFactory&
{
    static IrixALBackendFactory factory{};
    return factory;
}

auto IrixALBackendFactory::init() -> bool
{ return true; }

auto IrixALBackendFactory::querySupport(BackendType const type) -> bool
{ return type == BackendType::Playback; }

auto IrixALBackendFactory::enumerate(BackendType const type) -> std::vector<std::string>
{
    if(type == BackendType::Playback && DeviceRate() != 0)
        return std::vector{std::string{GetDefaultName()}};
    return {};
}

auto IrixALBackendFactory::createBackend(gsl::not_null<DeviceBase*> const device,
    BackendType const type) -> BackendPtr
{
    if(type == BackendType::Playback)
        return BackendPtr{new IrixALBackend{device}};
    return nullptr;
}
