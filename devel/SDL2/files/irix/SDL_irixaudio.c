/*
  SDL audio on IRIX: the Audio Library (libaudio, <dmedia/audio.h>).

  Playback through an output port on the default output device. Its
  sample rate is the system's, shared by every program playing on it, so
  the device is opened at that rate and SDL converts to it; the rate is
  never changed. Samples are 16-bit, mono or stereo. alWriteFrames blocks
  until the port's queue has room for a period, which paces SDL's audio
  thread. Without an Audio Library device the driver is not available.
*/
#include "../../SDL_internal.h"

#ifdef SDL_AUDIO_DRIVER_IRIX

#include <errno.h>

#include "SDL_audio.h"
#include "../SDL_audio_c.h"
#include "SDL_irixaudio.h"

#include <dmedia/audio.h>

/* The last Audio Library error, as text. */
static const char *IRIXAUDIO_Error(void)
{
    const char *str = alGetErrorString(errno);
    return str ? str : "unknown error";
}

/* The default output device's sample rate: 0 if it cannot be read. */
static int IRIXAUDIO_DeviceRate(void)
{
    ALpv pv;
    double rate;

    SDL_zero(pv);
    pv.param = AL_RATE;
    if (alGetParams(AL_DEFAULT_OUTPUT, &pv, 1) < 0 || pv.sizeOut < 0) {
        return 0;
    }
    rate = alFixedToDouble(pv.value.ll);
    if (!(rate >= 8000.0 && rate <= 192000.0)) {
        return 0;
    }
    return (int)(rate + 0.5);
}

static void IRIXAUDIO_PlayDevice(_THIS)
{
    if (alWriteFrames((ALport)this->hidden->port, this->hidden->mixbuf, this->hidden->frames) < 0) {
        SDL_OpenedAudioDeviceDisconnected(this);
    }
}

static Uint8 *IRIXAUDIO_GetDeviceBuf(_THIS)
{
    return this->hidden->mixbuf;
}

static void IRIXAUDIO_CloseDevice(_THIS)
{
    if (this->hidden->port) {
        alClosePort((ALport)this->hidden->port);
    }
    SDL_free(this->hidden->mixbuf);
    SDL_free(this->hidden);
}

static int IRIXAUDIO_OpenDevice(_THIS, const char *devname)
{
    ALconfig config;
    int rate;

    (void)devname;  /* the default output device alone */
    this->hidden = (struct SDL_PrivateAudioData *)SDL_malloc(sizeof(*this->hidden));
    if (!this->hidden) {
        return SDL_OutOfMemory();
    }
    SDL_zerop(this->hidden);

    rate = IRIXAUDIO_DeviceRate();
    if (rate) {
        this->spec.freq = rate;
    }
    this->spec.channels = (this->spec.channels >= 2) ? 2 : 1;
    this->spec.format = AUDIO_S16SYS;
    SDL_CalculateAudioSpec(&this->spec);
    this->hidden->frames = this->spec.samples;

    config = alNewConfig();
    if (!config) {
        return SDL_SetError("alNewConfig failed: %s", IRIXAUDIO_Error());
    }
    /* The port's queue holds two periods. */
    if (alSetSampFmt(config, AL_SAMPFMT_TWOSCOMP) < 0 ||
        alSetWidth(config, AL_SAMPLE_16) < 0 ||
        alSetChannels(config, this->spec.channels) < 0 ||
        alSetQueueSize(config, 2 * this->hidden->frames) < 0) {
        const char *err = IRIXAUDIO_Error();
        alFreeConfig(config);
        return SDL_SetError("Could not configure the audio port: %s", err);
    }
    this->hidden->port = alOpenPort("SDL audio", "w", config);
    alFreeConfig(config);
    if (!this->hidden->port) {
        return SDL_SetError("alOpenPort failed: %s", IRIXAUDIO_Error());
    }

    this->hidden->mixbuf = (Uint8 *)SDL_malloc(this->spec.size);
    if (!this->hidden->mixbuf) {
        return SDL_OutOfMemory();
    }
    SDL_memset(this->hidden->mixbuf, this->spec.silence, this->spec.size);

    return 0;
}

static SDL_bool IRIXAUDIO_Init(SDL_AudioDriverImpl *impl)
{
    if (!IRIXAUDIO_DeviceRate()) {
        return SDL_FALSE;   /* no Audio Library device */
    }

    impl->OpenDevice = IRIXAUDIO_OpenDevice;
    impl->PlayDevice = IRIXAUDIO_PlayDevice;
    impl->GetDeviceBuf = IRIXAUDIO_GetDeviceBuf;
    impl->CloseDevice = IRIXAUDIO_CloseDevice;
    impl->OnlyHasDefaultOutputDevice = SDL_TRUE;

    return SDL_TRUE;
}

AudioBootStrap IRIXAUDIO_bootstrap = {
    "irix", "IRIX Audio Library", IRIXAUDIO_Init, SDL_FALSE
};

#endif /* SDL_AUDIO_DRIVER_IRIX */

/* vi: set ts=4 sw=4 expandtab: */
