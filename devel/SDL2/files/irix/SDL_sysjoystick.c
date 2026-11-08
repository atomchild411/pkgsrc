/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#ifdef SDL_JOYSTICK_IRIX

/*
 * IRIX joysticks (pkgsrc). IRIX itself has no game controller devices;
 * under the revenir emulator, /dev/input/eventN is the host's Nth gamepad,
 * as a Linux evdev device in IRIX's ABI (SDL_revenir_input.h, revenir's
 * <revenir/input.h>). This is SDL's Linux evdev driver
 * (src/joystick/linux/SDL_sysjoystick.c) cut down to those devices: no
 * udev, inotify, classic /dev/input/js* devices, separate sensor devices or
 * Steam Controller. On SGI hardware /dev/input does not exist, and this
 * driver finds nothing.
 *
 * revenir's devices differ from Linux's in how they are found:
 *   - the gamepads are /dev/input/event0, 1, ... up to the first ENOENT;
 *     there is nothing to watch, so we probe again every few seconds;
 *   - numbers are not kept for a gamepad (the host's are counted again at
 *     each open: when gamepad 0 goes away, 1 becomes 0), so a device is
 *     known by its identity (EVIOCGUNIQ, EVIOCGPHYS, EVIOCGID, EVIOCGNAME),
 *     not by its path, and the path is looked up again when it is opened;
 *   - an open device gives ENODEV once it is gone.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "SDL_hints.h"
#include "SDL_joystick.h"
#include "SDL_log.h"
#include "SDL_timer.h"
#include "../../events/SDL_events_c.h"
#include "../SDL_sysjoystick.h"
#include "../SDL_joystick_c.h"
#include "../usb_ids.h"
#include "SDL_revenir_input.h"

#ifndef KEY_RECORD
#define KEY_RECORD 0xa7
#endif
#define IRIX_BTN_TRIGGER_HAPPY5 (BTN_TRIGGER_HAPPY + 4)
#define IRIX_BTN_TRIGGER_HAPPY6 (BTN_TRIGGER_HAPPY + 5)
#define IRIX_BTN_TRIGGER_HAPPY7 (BTN_TRIGGER_HAPPY + 6)
#define IRIX_BTN_TRIGGER_HAPPY8 (BTN_TRIGGER_HAPPY + 7)

#define IRIX_MAX_EVENT_DEVICES 32         /* stop probing there, whatever happens */
#define IRIX_DETECT_INTERVAL_MS 3000      /* how often to look for new gamepads */
#define IRIX_IDENTITY_SIZE 512

/* The private structure used to keep track of a joystick */
struct joystick_hwdata
{
    int fd;
    struct SDL_joylist_item *item;
    SDL_JoystickGUID guid;

    SDL_bool ff_rumble;
    SDL_bool ff_sine;
    struct ff_effect effect;

    struct hwdata_hat
    {
        int axis[2];
    } *hats;
    struct hwdata_ball
    {
        int axis[2];
    } *balls;

    Uint8 key_map[KEY_MAX];
    Uint8 abs_map[ABS_MAX];
    SDL_bool has_key[KEY_MAX];
    SDL_bool has_abs[ABS_MAX];

    struct axis_correct
    {
        SDL_bool use_deadzones;
        int coef[3];
        int minimum;
        int maximum;
        float scale;
    } abs_correct[ABS_MAX];

    /* 4 = (ABS_HAT3X-ABS_HAT0X)/2 */
    int hats_indices[4];
    SDL_bool has_hat[4];
    struct hat_axis_correct
    {
        SDL_bool use_deadzones;
        int minimum[2];
        int maximum[2];
    } hat_correct[4];

    SDL_bool fresh;
    SDL_bool recovering_from_dropped;

    /* Set when the gamepad is gone (ENODEV on read) */
    SDL_bool gone;
};

/* A linked list of available joysticks */
typedef struct SDL_joylist_item
{
    SDL_JoystickID device_instance;
    char *path;     /* "/dev/input/event0": where it was last seen */
    char *name;
    char *identity; /* what tells it from the others (see GetIdentity) */
    SDL_JoystickGUID guid;
    struct joystick_hwdata *hwdata;
    struct SDL_joylist_item *next;
    SDL_bool seen;  /* found by the current scan */

    SDL_bool checked_mapping;
    SDL_GamepadMapping *mapping;
} SDL_joylist_item;

static SDL_joylist_item *SDL_joylist SDL_GUARDED_BY(SDL_joystick_lock) = NULL;
static SDL_joylist_item *SDL_joylist_tail SDL_GUARDED_BY(SDL_joystick_lock) = NULL;
static int numjoysticks SDL_GUARDED_BY(SDL_joystick_lock) = 0;
static Uint32 last_joy_detect_time;

static int OpenDevice(const char *path, int flags)
{
    int fd = open(path, flags, 0);
    if (fd >= 0) {
        fcntl(fd, F_SETFD, FD_CLOEXEC);
    }
    return fd;
}

/* Something with buttons in a joystick or gamepad range, or with axes:
   revenir only shows gamepads, but be careful anyway. */
static SDL_bool GuessIsJoystick(int fd)
{
    unsigned long keybit[NBITS(KEY_MAX)];
    unsigned long absbit[NBITS(ABS_MAX)];
    int i;

    SDL_zeroa(keybit);
    SDL_zeroa(absbit);
    if (ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keybit)), keybit) < 0 ||
        ioctl(fd, EVIOCGBIT(EV_ABS, sizeof(absbit)), absbit) < 0) {
        return SDL_FALSE;
    }
    for (i = BTN_JOYSTICK; i <= BTN_THUMBR; ++i) {
        if (test_bit(i, keybit)) {
            return SDL_TRUE;
        }
    }
    for (i = BTN_TRIGGER_HAPPY; i <= BTN_TRIGGER_HAPPY40; ++i) {
        if (test_bit(i, keybit)) {
            return SDL_TRUE;
        }
    }
    return (test_bit(ABS_X, absbit) && test_bit(ABS_Y, absbit)) ? SDL_TRUE : SDL_FALSE;
}

/* What identifies a gamepad while it stays plugged in: its unique id (the
   DualSense's MAC address), physical path, bus/vendor/product/version and
   name. Identical gamepads without a unique id are told apart by the order
   they come in (see ScanDevices). */
static SDL_bool GetIdentity(int fd, char *identity, size_t size, struct input_id *inpid, char *name, size_t namesize)
{
    char uniq[128], phys[128];

    SDL_zerop(inpid);
    SDL_memset(name, 0, namesize);
    SDL_zeroa(uniq);
    SDL_zeroa(phys);
    if (ioctl(fd, EVIOCGID, inpid) < 0) {
        return SDL_FALSE;
    }
    if (ioctl(fd, EVIOCGNAME(namesize - 1), name) < 0) {
        return SDL_FALSE;
    }
    (void)ioctl(fd, EVIOCGUNIQ(sizeof(uniq) - 1), uniq);
    (void)ioctl(fd, EVIOCGPHYS(sizeof(phys) - 1), phys);
    SDL_snprintf(identity, size, "%s|%s|%04x:%04x:%04x:%04x|%s",
                 uniq, phys, inpid->bustype, inpid->vendor, inpid->product, inpid->version, name);
    return SDL_TRUE;
}

static void FreeJoylistItem(SDL_joylist_item *item)
{
    SDL_free(item->mapping);
    SDL_free(item->path);
    SDL_free(item->name);
    SDL_free(item->identity);
    SDL_free(item);
}

static void AddDevice(const char *path, const char *identity, struct input_id *inpid, const char *product_string)
{
    SDL_joylist_item *item;
    char *name;
    SDL_JoystickGUID guid;

    SDL_AssertJoysticksLocked();

    name = SDL_CreateJoystickName(inpid->vendor, inpid->product, NULL, product_string);
    if (!name) {
        return;
    }
    guid = SDL_CreateJoystickGUID(inpid->bustype, inpid->vendor, inpid->product, inpid->version, NULL, product_string, 0, 0);
    if (SDL_ShouldIgnoreJoystick(name, guid)) {
        SDL_free(name);
        return;
    }

    item = (SDL_joylist_item *)SDL_calloc(1, sizeof(SDL_joylist_item));
    if (!item) {
        SDL_free(name);
        return;
    }
    item->path = SDL_strdup(path);
    item->identity = SDL_strdup(identity);
    item->name = name;
    item->guid = guid;
    item->seen = SDL_TRUE;
    if (!item->path || !item->identity) {
        FreeJoylistItem(item);
        return;
    }

    item->device_instance = SDL_GetNextJoystickInstanceID();
    if (!SDL_joylist_tail) {
        SDL_joylist = SDL_joylist_tail = item;
    } else {
        SDL_joylist_tail->next = item;
        SDL_joylist_tail = item;
    }

    /* Need to increment the joystick count before we post the event */
    ++numjoysticks;

    SDL_PrivateJoystickAdded(item->device_instance);
}

static void RemoveJoylistItem(SDL_joylist_item *item, SDL_joylist_item *prev)
{
    SDL_AssertJoysticksLocked();

    if (item->hwdata) {
        item->hwdata->item = NULL;
    }

    if (prev) {
        prev->next = item->next;
    } else {
        SDL_assert(SDL_joylist == item);
        SDL_joylist = item->next;
    }

    if (item == SDL_joylist_tail) {
        SDL_joylist_tail = prev;
    }

    /* Need to decrement the joystick count before we post the event */
    --numjoysticks;

    SDL_PrivateJoystickRemoved(item->device_instance);
    FreeJoylistItem(item);
}

/* The devices found by one pass over /dev/input/event0, 1, ... */
typedef struct
{
    int count;
    struct
    {
        char path[32];
        char identity[IRIX_IDENTITY_SIZE];
        char product_string[128];
        struct input_id inpid;
    } dev[IRIX_MAX_EVENT_DEVICES];
} IRIX_DeviceScan;

/* Probe /dev/input/event0, 1, ... up to the first ENOENT, for gamepads.
   Identical gamepads without a unique id get "#1", "#2", ... in the order
   they come. */
static void ProbeDevices(IRIX_DeviceScan *scan)
{
    int i;

    scan->count = 0;
    for (i = 0; i < IRIX_MAX_EVENT_DEVICES; ++i) {
        char path[32];
        int fd, j, dups = 0;
        char *identity = scan->dev[scan->count].identity;

        SDL_snprintf(path, sizeof(path), "/dev/input/event%d", i);
        fd = OpenDevice(path, O_RDONLY | O_NONBLOCK);
        if (fd < 0) {
            if (errno == ENOENT || errno == ENOTDIR) {
                break; /* no more gamepads (or no /dev/input: not revenir) */
            }
            continue; /* busy, no permission...: look at the next one */
        }
        if (!GuessIsJoystick(fd) ||
            !GetIdentity(fd, identity, IRIX_IDENTITY_SIZE, &scan->dev[scan->count].inpid,
                         scan->dev[scan->count].product_string,
                         sizeof(scan->dev[scan->count].product_string))) {
            close(fd);
            continue;
        }
        close(fd);

        for (j = 0; j < scan->count; ++j) {
            if (SDL_strncmp(scan->dev[j].identity, identity, SDL_strlen(identity)) == 0) {
                ++dups;
            }
        }
        if (dups) {
            size_t len = SDL_strlen(identity);
            SDL_snprintf(identity + len, IRIX_IDENTITY_SIZE - len, "#%d", dups);
        }
        SDL_strlcpy(scan->dev[scan->count].path, path, sizeof(scan->dev[scan->count].path));
        ++scan->count;
    }
}

/* Where the gamepad with this identity is now; the list is not changed. */
static SDL_bool FindDevicePath(const char *identity, char *path, size_t size)
{
    IRIX_DeviceScan *scan = (IRIX_DeviceScan *)SDL_malloc(sizeof(*scan));
    SDL_bool found = SDL_FALSE;
    int i;

    if (!scan) {
        return SDL_FALSE;
    }
    ProbeDevices(scan);
    for (i = 0; i < scan->count; ++i) {
        if (SDL_strcmp(scan->dev[i].identity, identity) == 0) {
            SDL_strlcpy(path, scan->dev[i].path, size);
            found = SDL_TRUE;
            break;
        }
    }
    SDL_free(scan);
    return found;
}

/* Update the list: new gamepads are added; ones no longer there are removed
   (unless open: an open one goes when a read gives ENODEV). */
static void ScanDevices(void)
{
    SDL_joylist_item *item, *prev, *next;
    IRIX_DeviceScan *scan;
    int i;

    SDL_AssertJoysticksLocked();

    scan = (IRIX_DeviceScan *)SDL_malloc(sizeof(*scan));
    if (!scan) {
        return;
    }
    ProbeDevices(scan);

    for (item = SDL_joylist; item; item = item->next) {
        item->seen = SDL_FALSE;
    }

    for (i = 0; i < scan->count; ++i) {
        const char *path = scan->dev[i].path;
        const char *identity = scan->dev[i].identity;

        for (item = SDL_joylist; item; item = item->next) {
            if (SDL_strcmp(item->identity, identity) == 0) {
                break;
            }
        }
        if (item) {
            item->seen = SDL_TRUE;
            if (SDL_strcmp(item->path, path) != 0) {
                char *newpath = SDL_strdup(path);
                if (newpath) {
                    SDL_free(item->path);
                    item->path = newpath;
                }
            }
        } else {
            AddDevice(path, identity, &scan->dev[i].inpid, scan->dev[i].product_string);
        }
    }
    SDL_free(scan);

    prev = NULL;
    for (item = SDL_joylist; item; item = next) {
        next = item->next;
        if ((!item->seen && !item->hwdata) || (item->hwdata && item->hwdata->gone)) {
            RemoveJoylistItem(item, prev);
        } else {
            prev = item;
        }
    }
}

static void IRIX_JoystickDetect(void)
{
    Uint32 now = SDL_GetTicks();

    SDL_AssertJoysticksLocked();

    if (!last_joy_detect_time || SDL_TICKS_PASSED(now, last_joy_detect_time + IRIX_DETECT_INTERVAL_MS)) {
        ScanDevices();
        last_joy_detect_time = now;
    } else {
        /* Between scans, only drop the gamepads found gone */
        SDL_joylist_item *item, *prev = NULL, *next;
        for (item = SDL_joylist; item; item = next) {
            next = item->next;
            if (item->hwdata && item->hwdata->gone) {
                RemoveJoylistItem(item, prev);
            } else {
                prev = item;
            }
        }
    }
}

static int IRIX_JoystickInit(void)
{
    last_joy_detect_time = 0;
    IRIX_JoystickDetect();
    return 0;
}

static int IRIX_JoystickGetCount(void)
{
    SDL_AssertJoysticksLocked();

    return numjoysticks;
}

static SDL_joylist_item *JoystickByDevIndex(int device_index)
{
    SDL_joylist_item *item;

    SDL_AssertJoysticksLocked();

    if ((device_index < 0) || (device_index >= numjoysticks)) {
        return NULL;
    }

    item = SDL_joylist;
    while (device_index > 0) {
        SDL_assert(item != NULL);
        device_index--;
        item = item->next;
    }

    return item;
}

static const char *IRIX_JoystickGetDeviceName(int device_index)
{
    return JoystickByDevIndex(device_index)->name;
}

static const char *IRIX_JoystickGetDevicePath(int device_index)
{
    return JoystickByDevIndex(device_index)->path;
}

static int IRIX_JoystickGetDeviceSteamVirtualGamepadSlot(int device_index)
{
    return -1;
}

static int IRIX_JoystickGetDevicePlayerIndex(int device_index)
{
    return -1;
}

static void IRIX_JoystickSetDevicePlayerIndex(int device_index, int player_index)
{
}

static SDL_JoystickGUID IRIX_JoystickGetDeviceGUID(int device_index)
{
    return JoystickByDevIndex(device_index)->guid;
}

static SDL_JoystickID IRIX_JoystickGetDeviceInstanceID(int device_index)
{
    return JoystickByDevIndex(device_index)->device_instance;
}

static int allocate_hatdata(SDL_Joystick *joystick)
{
    int i;

    SDL_AssertJoysticksLocked();

    joystick->hwdata->hats =
        (struct hwdata_hat *)SDL_malloc(joystick->nhats *
                                        sizeof(struct hwdata_hat));
    if (!joystick->hwdata->hats) {
        return -1;
    }
    for (i = 0; i < joystick->nhats; ++i) {
        joystick->hwdata->hats[i].axis[0] = 1;
        joystick->hwdata->hats[i].axis[1] = 1;
    }
    return 0;
}

static int allocate_balldata(SDL_Joystick *joystick)
{
    int i;

    SDL_AssertJoysticksLocked();

    joystick->hwdata->balls =
        (struct hwdata_ball *)SDL_malloc(joystick->nballs *
                                         sizeof(struct hwdata_ball));
    if (!joystick->hwdata->balls) {
        return -1;
    }
    for (i = 0; i < joystick->nballs; ++i) {
        joystick->hwdata->balls[i].axis[0] = 0;
        joystick->hwdata->balls[i].axis[1] = 0;
    }
    return 0;
}

static SDL_bool GuessIfAxesAreDigitalHat(struct input_absinfo *absinfo_x, struct input_absinfo *absinfo_y)
{
    /* As SDL's Linux driver: a "hat" has at most 3 states per axis. */
    if (!absinfo_x && !absinfo_y) {
        return SDL_FALSE;
    }
    if (SDL_GetHintBoolean(SDL_HINT_LINUX_DIGITAL_HATS, SDL_FALSE)) {
        return SDL_TRUE;
    }
    if ((!absinfo_x || (absinfo_x->minimum == -1 && absinfo_x->maximum == 1)) && (!absinfo_y || (absinfo_y->minimum == -1 && absinfo_y->maximum == 1))) {
        return SDL_TRUE;
    }
    if ((!absinfo_x || (!absinfo_x->fuzz && !absinfo_x->flat && !absinfo_x->resolution)) && (!absinfo_y || (!absinfo_y->fuzz && !absinfo_y->flat && !absinfo_y->resolution))) {
        return SDL_TRUE;
    }
    return SDL_FALSE;
}

static void ConfigJoystick(SDL_Joystick *joystick, int fd)
{
    int i, t;
    unsigned long keybit[NBITS(KEY_MAX)];
    unsigned long absbit[NBITS(ABS_MAX)];
    unsigned long relbit[NBITS(REL_MAX)];
    unsigned long ffbit[NBITS(FF_MAX)];
    SDL_bool use_deadzones = SDL_GetHintBoolean(SDL_HINT_LINUX_JOYSTICK_DEADZONES, SDL_FALSE);
    SDL_bool use_hat_deadzones = SDL_GetHintBoolean(SDL_HINT_LINUX_HAT_DEADZONES, SDL_TRUE);

    SDL_AssertJoysticksLocked();

    SDL_zeroa(keybit);
    SDL_zeroa(absbit);
    SDL_zeroa(relbit);
    SDL_zeroa(ffbit);

    if ((ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(keybit)), keybit) >= 0) &&
        (ioctl(fd, EVIOCGBIT(EV_ABS, sizeof(absbit)), absbit) >= 0) &&
        (ioctl(fd, EVIOCGBIT(EV_REL, sizeof(relbit)), relbit) >= 0)) {

        /* Get the number of buttons, axes, and other thingamajigs */
        for (i = BTN_JOYSTICK; i < KEY_MAX; ++i) {
            if (test_bit(i, keybit)) {
                joystick->hwdata->key_map[i] = joystick->nbuttons;
                joystick->hwdata->has_key[i] = SDL_TRUE;
                ++joystick->nbuttons;
            }
        }
        for (i = 0; i < BTN_JOYSTICK; ++i) {
            if (test_bit(i, keybit)) {
                joystick->hwdata->key_map[i] = joystick->nbuttons;
                joystick->hwdata->has_key[i] = SDL_TRUE;
                ++joystick->nbuttons;
            }
        }
        for (i = ABS_HAT0X; i <= ABS_HAT3Y; i += 2) {
            int hat_x = -1;
            int hat_y = -1;
            struct input_absinfo absinfo_x;
            struct input_absinfo absinfo_y;
            if (test_bit(i, absbit)) {
                hat_x = ioctl(fd, EVIOCGABS(i), &absinfo_x);
            }
            if (test_bit(i + 1, absbit)) {
                hat_y = ioctl(fd, EVIOCGABS(i + 1), &absinfo_y);
            }
            if (GuessIfAxesAreDigitalHat((hat_x < 0 ? (void *)0 : &absinfo_x),
                                         (hat_y < 0 ? (void *)0 : &absinfo_y))) {
                const int hat_index = (i - ABS_HAT0X) / 2;
                struct hat_axis_correct *correct = &joystick->hwdata->hat_correct[hat_index];
                joystick->hwdata->hats_indices[hat_index] = joystick->nhats;
                joystick->hwdata->has_hat[hat_index] = SDL_TRUE;
                correct->use_deadzones = use_hat_deadzones;
                correct->minimum[0] = (hat_x < 0) ? -1 : absinfo_x.minimum;
                correct->maximum[0] = (hat_x < 0) ? 1 : absinfo_x.maximum;
                correct->minimum[1] = (hat_y < 0) ? -1 : absinfo_y.minimum;
                correct->maximum[1] = (hat_y < 0) ? 1 : absinfo_y.maximum;
                ++joystick->nhats;
            }
        }
        for (i = 0; i < ABS_MAX; ++i) {
            /* Skip digital hats */
            if (i >= ABS_HAT0X && i <= ABS_HAT3Y && joystick->hwdata->has_hat[(i - ABS_HAT0X) / 2]) {
                continue;
            }
            if (test_bit(i, absbit)) {
                struct input_absinfo absinfo;
                struct axis_correct *correct = &joystick->hwdata->abs_correct[i];

                if (ioctl(fd, EVIOCGABS(i), &absinfo) < 0) {
                    continue;
                }
                joystick->hwdata->abs_map[i] = joystick->naxes;
                joystick->hwdata->has_abs[i] = SDL_TRUE;

                correct->minimum = absinfo.minimum;
                correct->maximum = absinfo.maximum;
                if (correct->minimum != correct->maximum) {
                    if (use_deadzones) {
                        correct->use_deadzones = SDL_TRUE;
                        correct->coef[0] = (absinfo.maximum + absinfo.minimum) - 2 * absinfo.flat;
                        correct->coef[1] = (absinfo.maximum + absinfo.minimum) + 2 * absinfo.flat;
                        t = ((absinfo.maximum - absinfo.minimum) - 4 * absinfo.flat);
                        if (t != 0) {
                            correct->coef[2] = (1 << 28) / t;
                        } else {
                            correct->coef[2] = 0;
                        }
                    } else {
                        float value_range = (float)(correct->maximum - correct->minimum);
                        float output_range = (SDL_JOYSTICK_AXIS_MAX - SDL_JOYSTICK_AXIS_MIN);

                        correct->scale = (output_range / value_range);
                    }
                }
                ++joystick->naxes;
            }
        }
        if (test_bit(REL_X, relbit) || test_bit(REL_Y, relbit)) {
            ++joystick->nballs;
        }
    }

    /* Allocate data to keep track of these thingamajigs */
    if (joystick->nhats > 0) {
        if (allocate_hatdata(joystick) < 0) {
            joystick->nhats = 0;
        }
    }
    if (joystick->nballs > 0) {
        if (allocate_balldata(joystick) < 0) {
            joystick->nballs = 0;
        }
    }

    if (ioctl(fd, EVIOCGBIT(EV_FF, sizeof(ffbit)), ffbit) >= 0) {
        if (test_bit(FF_RUMBLE, ffbit)) {
            joystick->hwdata->ff_rumble = SDL_TRUE;
        }
        if (test_bit(FF_SINE, ffbit)) {
            joystick->hwdata->ff_sine = SDL_TRUE;
        }
    }
}

/* Open the gamepad behind item (wherever it is now) and fill in hwdata.
   Expects joystick->hwdata allocated; does not free it on error. */
static int PrepareJoystickHwdata(SDL_Joystick *joystick, SDL_joylist_item *item)
{
    char path[32];
    char identity[IRIX_IDENTITY_SIZE];
    char product_string[128];
    struct input_id inpid;
    int fd;

    SDL_AssertJoysticksLocked();

    joystick->hwdata->item = item;
    joystick->hwdata->guid = item->guid;
    joystick->hwdata->effect.id = -1;
    joystick->hwdata->fd = -1;
    SDL_memset(joystick->hwdata->key_map, 0xFF, sizeof(joystick->hwdata->key_map));
    SDL_memset(joystick->hwdata->abs_map, 0xFF, sizeof(joystick->hwdata->abs_map));

    /* Numbers move: look for it again, then check what we opened */
    SDL_strlcpy(path, item->path, sizeof(path));
    if (!FindDevicePath(item->identity, path, sizeof(path))) {
        return SDL_SetError("%s is gone", item->name);
    }

    /* Try read-write first, so we can do rumble */
    fd = OpenDevice(path, O_RDWR);
    if (fd < 0) {
        /* Try read-only again, at least we'll get events in this case */
        fd = OpenDevice(path, O_RDONLY);
    }
    if (fd < 0) {
        return SDL_SetError("Unable to open %s", path);
    }
    if (!GetIdentity(fd, identity, sizeof(identity), &inpid, product_string, sizeof(product_string)) ||
        SDL_strncmp(identity, item->identity, SDL_strlen(identity)) != 0) {
        close(fd);
        return SDL_SetError("Joystick %s moved while being opened", item->name);
    }

    joystick->hwdata->fd = fd;

    /* Set the joystick to non-blocking read mode */
    fcntl(fd, F_SETFL, O_NONBLOCK);

    /* Get the number of buttons and axes on the joystick */
    ConfigJoystick(joystick, fd);
    return 0;
}

static int IRIX_JoystickOpen(SDL_Joystick *joystick, int device_index)
{
    SDL_joylist_item *item;

    SDL_AssertJoysticksLocked();

    item = JoystickByDevIndex(device_index);
    if (!item) {
        return SDL_SetError("No such device");
    }

    joystick->instance_id = item->device_instance;
    joystick->hwdata = (struct joystick_hwdata *)
        SDL_calloc(1, sizeof(*joystick->hwdata));
    if (!joystick->hwdata) {
        return SDL_OutOfMemory();
    }

    if (PrepareJoystickHwdata(joystick, item) == -1) {
        SDL_free(joystick->hwdata);
        joystick->hwdata = NULL;
        return -1; /* SDL_SetError will already have been called */
    }

    SDL_assert(item->hwdata == NULL);
    item->hwdata = joystick->hwdata;

    /* mark joystick as fresh and ready */
    joystick->hwdata->fresh = SDL_TRUE;

    return 0;
}

static int IRIX_JoystickRumble(SDL_Joystick *joystick, Uint16 low_frequency_rumble, Uint16 high_frequency_rumble)
{
    struct input_event event;

    SDL_AssertJoysticksLocked();

    if (joystick->hwdata->ff_rumble) {
        struct ff_effect *effect = &joystick->hwdata->effect;

        effect->type = FF_RUMBLE;
        effect->replay.length = SDL_MAX_RUMBLE_DURATION_MS;
        effect->u.rumble.strong_magnitude = low_frequency_rumble;
        effect->u.rumble.weak_magnitude = high_frequency_rumble;
    } else if (joystick->hwdata->ff_sine) {
        /* Scale and average the two rumble strengths */
        Sint16 magnitude = (Sint16)(((low_frequency_rumble / 2) + (high_frequency_rumble / 2)) / 2);
        struct ff_effect *effect = &joystick->hwdata->effect;

        effect->type = FF_PERIODIC;
        effect->replay.length = SDL_MAX_RUMBLE_DURATION_MS;
        effect->u.periodic.waveform = FF_SINE;
        effect->u.periodic.magnitude = magnitude;
    } else {
        return SDL_Unsupported();
    }

    if (ioctl(joystick->hwdata->fd, EVIOCSFF, &joystick->hwdata->effect) < 0) {
        /* The effect may have been lost, try to allocate a new one */
        joystick->hwdata->effect.id = -1;
        if (ioctl(joystick->hwdata->fd, EVIOCSFF, &joystick->hwdata->effect) < 0) {
            return SDL_SetError("Couldn't update rumble effect: %s", strerror(errno));
        }
    }

    SDL_zero(event);
    event.type = EV_FF;
    event.code = joystick->hwdata->effect.id;
    event.value = 1;
    if (write(joystick->hwdata->fd, &event, sizeof(event)) < 0) {
        return SDL_SetError("Couldn't start rumble effect: %s", strerror(errno));
    }
    return 0;
}

static int IRIX_JoystickRumbleTriggers(SDL_Joystick *joystick, Uint16 left_rumble, Uint16 right_rumble)
{
    return SDL_Unsupported();
}

static Uint32 IRIX_JoystickGetCapabilities(SDL_Joystick *joystick)
{
    Uint32 result = 0;

    SDL_AssertJoysticksLocked();

    if (joystick->hwdata->ff_rumble || joystick->hwdata->ff_sine) {
        result |= SDL_JOYCAP_RUMBLE;
    }

    return result;
}

static int IRIX_JoystickSetLED(SDL_Joystick *joystick, Uint8 red, Uint8 green, Uint8 blue)
{
    return SDL_Unsupported();
}

static int IRIX_JoystickSendEffect(SDL_Joystick *joystick, const void *data, int size)
{
    return SDL_Unsupported();
}

static int IRIX_JoystickSetSensorsEnabled(SDL_Joystick *joystick, SDL_bool enabled)
{
    return SDL_Unsupported();
}

static void HandleHat(SDL_Joystick *stick, int hatidx, int axis, int value)
{
    int hatnum;
    struct hwdata_hat *the_hat;
    struct hat_axis_correct *correct;
    const Uint8 position_map[3][3] = {
        { SDL_HAT_LEFTUP, SDL_HAT_UP, SDL_HAT_RIGHTUP },
        { SDL_HAT_LEFT, SDL_HAT_CENTERED, SDL_HAT_RIGHT },
        { SDL_HAT_LEFTDOWN, SDL_HAT_DOWN, SDL_HAT_RIGHTDOWN }
    };

    SDL_AssertJoysticksLocked();

    hatnum = stick->hwdata->hats_indices[hatidx];
    the_hat = &stick->hwdata->hats[hatnum];
    correct = &stick->hwdata->hat_correct[hatidx];
    if (value < 0) {
        if (value <= correct->minimum[axis]) {
            correct->minimum[axis] = value;
            value = 0;
        } else if (!correct->use_deadzones || value < correct->minimum[axis] / 3) {
            value = 0;
        } else {
            value = 1;
        }
    } else if (value > 0) {
        if (value >= correct->maximum[axis]) {
            correct->maximum[axis] = value;
            value = 2;
        } else if (!correct->use_deadzones || value > correct->maximum[axis] / 3) {
            value = 2;
        } else {
            value = 1;
        }
    } else { /* value == 0 */
        value = 1;
    }
    if (value != the_hat->axis[axis]) {
        the_hat->axis[axis] = value;
        SDL_PrivateJoystickHat(stick, hatnum,
                               position_map[the_hat->axis[1]][the_hat->axis[0]]);
    }
}

static void HandleBall(SDL_Joystick *stick, Uint8 ball, int axis, int value)
{
    SDL_AssertJoysticksLocked();

    stick->hwdata->balls[ball].axis[axis] += value;
}

static int AxisCorrect(SDL_Joystick *joystick, int which, int value)
{
    struct axis_correct *correct;

    SDL_AssertJoysticksLocked();

    correct = &joystick->hwdata->abs_correct[which];
    if (correct->minimum != correct->maximum) {
        if (correct->use_deadzones) {
            value *= 2;
            if (value > correct->coef[0]) {
                if (value < correct->coef[1]) {
                    return 0;
                }
                value -= correct->coef[1];
            } else {
                value -= correct->coef[0];
            }
            value *= correct->coef[2];
            value >>= 13;
        } else {
            value = (int)SDL_floorf((value - correct->minimum) * correct->scale + SDL_JOYSTICK_AXIS_MIN + 0.5f);
        }
    }

    /* Clamp and return */
    if (value < SDL_JOYSTICK_AXIS_MIN) {
        return SDL_JOYSTICK_AXIS_MIN;
    }
    if (value > SDL_JOYSTICK_AXIS_MAX) {
        return SDL_JOYSTICK_AXIS_MAX;
    }
    return value;
}

static void PollAllValues(SDL_Joystick *joystick)
{
    struct input_absinfo absinfo;
    unsigned long keyinfo[NBITS(KEY_MAX)];
    int i;

    SDL_AssertJoysticksLocked();

    /* Poll all axis */
    for (i = ABS_X; i < ABS_MAX; i++) {
        /* We don't need to test for digital hats here, they won't have has_abs[] set */
        if (joystick->hwdata->has_abs[i]) {
            if (ioctl(joystick->hwdata->fd, EVIOCGABS(i), &absinfo) >= 0) {
                absinfo.value = AxisCorrect(joystick, i, absinfo.value);
                SDL_PrivateJoystickAxis(joystick,
                                        joystick->hwdata->abs_map[i],
                                        absinfo.value);
            }
        }
    }

    /* Poll all digital hats */
    for (i = ABS_HAT0X; i <= ABS_HAT3Y; i++) {
        const int baseaxis = i - ABS_HAT0X;
        const int hatidx = baseaxis / 2;
        if (joystick->hwdata->has_hat[hatidx]) {
            if (ioctl(joystick->hwdata->fd, EVIOCGABS(i), &absinfo) >= 0) {
                const int hataxis = baseaxis % 2;
                HandleHat(joystick, hatidx, hataxis, absinfo.value);
            }
        }
    }

    /* Poll all buttons */
    SDL_zeroa(keyinfo);
    if (ioctl(joystick->hwdata->fd, EVIOCGKEY(sizeof(keyinfo)), keyinfo) >= 0) {
        for (i = 0; i < KEY_MAX; i++) {
            if (joystick->hwdata->has_key[i]) {
                const Uint8 value = test_bit(i, keyinfo) ? SDL_PRESSED : SDL_RELEASED;
                SDL_PrivateJoystickButton(joystick,
                                          joystick->hwdata->key_map[i], value);
            }
        }
    }

    /* Joyballs are relative input, so there's no poll state. Events only! */
}

static void HandleInputEvents(SDL_Joystick *joystick)
{
    struct input_event events[32];
    int i, len, code, hat_index;

    SDL_AssertJoysticksLocked();

    if (joystick->hwdata->fresh) {
        PollAllValues(joystick);
        joystick->hwdata->fresh = SDL_FALSE;
    }

    errno = 0;

    while ((len = read(joystick->hwdata->fd, events, sizeof(events))) > 0) {
        len /= sizeof(events[0]);
        for (i = 0; i < len; ++i) {
            code = events[i].code;

            /* After a SYN_DROPPED, ignore the rest of the packet (up to a SYN_REPORT) */
            if (joystick->hwdata->recovering_from_dropped &&
                ((events[i].type != EV_SYN) || (code != SYN_REPORT))) {
                continue;
            }

            switch (events[i].type) {
            case EV_KEY:
                if (code < KEY_MAX && joystick->hwdata->has_key[code]) {
                    SDL_PrivateJoystickButton(joystick,
                                              joystick->hwdata->key_map[code],
                                              events[i].value);
                }
                break;
            case EV_ABS:
                if (code >= ABS_MAX) {
                    break;
                }
                switch (code) {
                case ABS_HAT0X:
                case ABS_HAT0Y:
                case ABS_HAT1X:
                case ABS_HAT1Y:
                case ABS_HAT2X:
                case ABS_HAT2Y:
                case ABS_HAT3X:
                case ABS_HAT3Y:
                    hat_index = (code - ABS_HAT0X) / 2;
                    if (joystick->hwdata->has_hat[hat_index]) {
                        HandleHat(joystick, hat_index, code % 2, events[i].value);
                        break;
                    }
                    SDL_FALLTHROUGH;
                default:
                    if (joystick->hwdata->has_abs[code]) {
                        events[i].value = AxisCorrect(joystick, code, events[i].value);
                        SDL_PrivateJoystickAxis(joystick,
                                                joystick->hwdata->abs_map[code],
                                                events[i].value);
                    }
                    break;
                }
                break;
            case EV_REL:
                switch (code) {
                case REL_X:
                case REL_Y:
                    if (joystick->nballs > 0) {
                        code -= REL_X;
                        HandleBall(joystick, code / 2, code % 2, events[i].value);
                    }
                    break;
                default:
                    break;
                }
                break;
            case EV_SYN:
                switch (code) {
                case SYN_DROPPED:
                    joystick->hwdata->recovering_from_dropped = SDL_TRUE;
                    break;
                case SYN_REPORT:
                    if (joystick->hwdata->recovering_from_dropped) {
                        joystick->hwdata->recovering_from_dropped = SDL_FALSE;
                        PollAllValues(joystick); /* try to sync up to current state now */
                    }
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
    }

    if (errno == ENODEV) {
        /* We have to wait until the JoystickDetect callback to remove this */
        joystick->hwdata->gone = SDL_TRUE;
        errno = 0;
    }
}

static void IRIX_JoystickUpdate(SDL_Joystick *joystick)
{
    int i;

    SDL_AssertJoysticksLocked();

    HandleInputEvents(joystick);

    /* Deliver ball motion updates */
    for (i = 0; i < joystick->nballs; ++i) {
        int xrel, yrel;

        xrel = joystick->hwdata->balls[i].axis[0];
        yrel = joystick->hwdata->balls[i].axis[1];
        if (xrel || yrel) {
            joystick->hwdata->balls[i].axis[0] = 0;
            joystick->hwdata->balls[i].axis[1] = 0;
            SDL_PrivateJoystickBall(joystick, (Uint8)i, xrel, yrel);
        }
    }
}

static void IRIX_JoystickClose(SDL_Joystick *joystick)
{
    SDL_AssertJoysticksLocked();

    if (joystick->hwdata) {
        if (joystick->hwdata->effect.id >= 0) {
            int id = joystick->hwdata->effect.id;
            ioctl(joystick->hwdata->fd, EVIOCRMFF, id);
            joystick->hwdata->effect.id = -1;
        }
        if (joystick->hwdata->fd >= 0) {
            close(joystick->hwdata->fd);
        }
        if (joystick->hwdata->item) {
            joystick->hwdata->item->hwdata = NULL;
        }
        SDL_free(joystick->hwdata->hats);
        SDL_free(joystick->hwdata->balls);
        SDL_free(joystick->hwdata);
    }
}

static void IRIX_JoystickQuit(void)
{
    SDL_joylist_item *item = NULL;
    SDL_joylist_item *next = NULL;

    SDL_AssertJoysticksLocked();

    for (item = SDL_joylist; item; item = next) {
        next = item->next;
        FreeJoylistItem(item);
    }

    SDL_joylist = SDL_joylist_tail = NULL;
    numjoysticks = 0;
    last_joy_detect_time = 0;
}

/*
   As SDL's Linux driver: a mapping from the evdev codes, after the Linux
   Gamepad Specification (https://www.kernel.org/doc/html/v4.15/input/gamepad.html)
   and the Android gamepad documentation.
 */
static SDL_bool IRIX_JoystickGetGamepadMapping(int device_index, SDL_GamepadMapping *out)
{
    SDL_Joystick *joystick;
    SDL_joylist_item *item = JoystickByDevIndex(device_index);
    enum {
        MAPPED_TRIGGER_LEFT = 0x1,
        MAPPED_TRIGGER_RIGHT = 0x2,
        MAPPED_TRIGGER_BOTH = 0x3,

        MAPPED_DPAD_UP = 0x1,
        MAPPED_DPAD_DOWN = 0x2,
        MAPPED_DPAD_LEFT = 0x4,
        MAPPED_DPAD_RIGHT = 0x8,
        MAPPED_DPAD_ALL = 0xF
    };
    unsigned int mapped;

    SDL_AssertJoysticksLocked();

    if (!item) {
        return SDL_FALSE;
    }
    if (item->checked_mapping) {
        if (item->mapping) {
            SDL_memcpy(out, item->mapping, sizeof(*out));
            return SDL_TRUE;
        } else {
            return SDL_FALSE;
        }
    }

    /* We temporarily open the device to check how it's configured. Make
       a fake SDL_Joystick object to do so. */
    joystick = (SDL_Joystick *)SDL_calloc(sizeof(*joystick), 1);
    if (!joystick) {
        SDL_OutOfMemory();
        return SDL_FALSE;
    }
    joystick->magic = &SDL_joystick_magic;
    SDL_memcpy(&joystick->guid, &item->guid, sizeof(item->guid));

    joystick->hwdata = (struct joystick_hwdata *)
        SDL_calloc(1, sizeof(*joystick->hwdata));
    if (!joystick->hwdata) {
        SDL_free(joystick);
        SDL_OutOfMemory();
        return SDL_FALSE;
    }

    item->checked_mapping = SDL_TRUE;

    if (PrepareJoystickHwdata(joystick, item) == -1) {
        SDL_free(joystick->hwdata);
        SDL_free(joystick);
        return SDL_FALSE; /* SDL_SetError will already have been called */
    }

    /* don't assign `item->hwdata` so it's not in any global state;
       clear hwdata->item so closing it doesn't touch the item either */
    joystick->hwdata->item = NULL;

    if (!joystick->hwdata->has_key[BTN_GAMEPAD]) {
        /* Not a gamepad according to the specs. */
        IRIX_JoystickClose(joystick);
        SDL_free(joystick);
        return SDL_FALSE;
    }

    if (joystick->hwdata->has_key[BTN_A]) {
        out->a.kind = EMappingKind_Button;
        out->a.target = joystick->hwdata->key_map[BTN_A];
    }

    if (joystick->hwdata->has_key[BTN_B]) {
        out->b.kind = EMappingKind_Button;
        out->b.target = joystick->hwdata->key_map[BTN_B];
    }

    /* Xbox controllers use BTN_X and BTN_Y, and PS4 controllers use BTN_WEST and BTN_NORTH */
    if (SDL_JoystickGetVendor(joystick) == USB_VENDOR_SONY) {
        if (joystick->hwdata->has_key[BTN_WEST]) {
            out->x.kind = EMappingKind_Button;
            out->x.target = joystick->hwdata->key_map[BTN_WEST];
        }

        if (joystick->hwdata->has_key[BTN_NORTH]) {
            out->y.kind = EMappingKind_Button;
            out->y.target = joystick->hwdata->key_map[BTN_NORTH];
        }
    } else {
        if (joystick->hwdata->has_key[BTN_X]) {
            out->x.kind = EMappingKind_Button;
            out->x.target = joystick->hwdata->key_map[BTN_X];
        }

        if (joystick->hwdata->has_key[BTN_Y]) {
            out->y.kind = EMappingKind_Button;
            out->y.target = joystick->hwdata->key_map[BTN_Y];
        }
    }

    if (joystick->hwdata->has_key[BTN_SELECT]) {
        out->back.kind = EMappingKind_Button;
        out->back.target = joystick->hwdata->key_map[BTN_SELECT];
    }

    if (joystick->hwdata->has_key[BTN_START]) {
        out->start.kind = EMappingKind_Button;
        out->start.target = joystick->hwdata->key_map[BTN_START];
    }

    if (joystick->hwdata->has_key[BTN_THUMBL]) {
        out->leftstick.kind = EMappingKind_Button;
        out->leftstick.target = joystick->hwdata->key_map[BTN_THUMBL];
    }

    if (joystick->hwdata->has_key[BTN_THUMBR]) {
        out->rightstick.kind = EMappingKind_Button;
        out->rightstick.target = joystick->hwdata->key_map[BTN_THUMBR];
    }

    if (joystick->hwdata->has_key[BTN_MODE]) {
        out->guide.kind = EMappingKind_Button;
        out->guide.target = joystick->hwdata->key_map[BTN_MODE];
    }

    /*
       According to the specs the D-Pad, the shoulder buttons and the triggers
       can be digital, or analog, or both at the same time.
     */

    /* Prefer digital shoulder buttons, but settle for digital or analog hat. */
    mapped = 0;

    if (joystick->hwdata->has_key[BTN_TL]) {
        out->leftshoulder.kind = EMappingKind_Button;
        out->leftshoulder.target = joystick->hwdata->key_map[BTN_TL];
        mapped |= 0x1;
    }

    if (joystick->hwdata->has_key[BTN_TR]) {
        out->rightshoulder.kind = EMappingKind_Button;
        out->rightshoulder.target = joystick->hwdata->key_map[BTN_TR];
        mapped |= 0x2;
    }

    if (mapped != 0x3 && joystick->hwdata->has_hat[1]) {
        int hat = joystick->hwdata->hats_indices[1] << 4;
        out->leftshoulder.kind = EMappingKind_Hat;
        out->rightshoulder.kind = EMappingKind_Hat;
        out->leftshoulder.target = hat | 0x4;
        out->rightshoulder.target = hat | 0x2;
        mapped |= 0x3;
    }

    if (!(mapped & 0x1) && joystick->hwdata->has_abs[ABS_HAT1Y]) {
        out->leftshoulder.kind = EMappingKind_Axis;
        out->leftshoulder.target = joystick->hwdata->abs_map[ABS_HAT1Y];
        mapped |= 0x1;
    }

    if (!(mapped & 0x2) && joystick->hwdata->has_abs[ABS_HAT1X]) {
        out->rightshoulder.kind = EMappingKind_Axis;
        out->rightshoulder.target = joystick->hwdata->abs_map[ABS_HAT1X];
        mapped |= 0x2;
    }

    /* Prefer analog triggers, but settle for digital hat or buttons.
     * Conventions: Linux Gamepad Specification (ABS_HAT2Y, ABS_HAT2X),
     * Android (ABS_BRAKE, ABS_GAS), older Xbox and Playstation (ABS_Z, ABS_RZ). */
    mapped = 0;

    if (joystick->hwdata->has_abs[ABS_HAT2Y]) {
        out->lefttrigger.kind = EMappingKind_Axis;
        out->lefttrigger.target = joystick->hwdata->abs_map[ABS_HAT2Y];
        mapped |= MAPPED_TRIGGER_LEFT;
    } else if (joystick->hwdata->has_abs[ABS_BRAKE]) {
        out->lefttrigger.kind = EMappingKind_Axis;
        out->lefttrigger.target = joystick->hwdata->abs_map[ABS_BRAKE];
        mapped |= MAPPED_TRIGGER_LEFT;
    } else if (joystick->hwdata->has_abs[ABS_Z]) {
        out->lefttrigger.kind = EMappingKind_Axis;
        out->lefttrigger.target = joystick->hwdata->abs_map[ABS_Z];
        mapped |= MAPPED_TRIGGER_LEFT;
    }

    if (joystick->hwdata->has_abs[ABS_HAT2X]) {
        out->righttrigger.kind = EMappingKind_Axis;
        out->righttrigger.target = joystick->hwdata->abs_map[ABS_HAT2X];
        mapped |= MAPPED_TRIGGER_RIGHT;
    } else if (joystick->hwdata->has_abs[ABS_GAS]) {
        out->righttrigger.kind = EMappingKind_Axis;
        out->righttrigger.target = joystick->hwdata->abs_map[ABS_GAS];
        mapped |= MAPPED_TRIGGER_RIGHT;
    } else if (joystick->hwdata->has_abs[ABS_RZ]) {
        out->righttrigger.kind = EMappingKind_Axis;
        out->righttrigger.target = joystick->hwdata->abs_map[ABS_RZ];
        mapped |= MAPPED_TRIGGER_RIGHT;
    }

    if (mapped != MAPPED_TRIGGER_BOTH && joystick->hwdata->has_hat[2]) {
        int hat = joystick->hwdata->hats_indices[2] << 4;
        out->lefttrigger.kind = EMappingKind_Hat;
        out->righttrigger.kind = EMappingKind_Hat;
        out->lefttrigger.target = hat | 0x4;
        out->righttrigger.target = hat | 0x2;
        mapped |= MAPPED_TRIGGER_BOTH;
    }

    if (!(mapped & MAPPED_TRIGGER_LEFT) && joystick->hwdata->has_key[BTN_TL2]) {
        out->lefttrigger.kind = EMappingKind_Button;
        out->lefttrigger.target = joystick->hwdata->key_map[BTN_TL2];
        mapped |= MAPPED_TRIGGER_LEFT;
    }

    if (!(mapped & MAPPED_TRIGGER_RIGHT) && joystick->hwdata->has_key[BTN_TR2]) {
        out->righttrigger.kind = EMappingKind_Button;
        out->righttrigger.target = joystick->hwdata->key_map[BTN_TR2];
        mapped |= MAPPED_TRIGGER_RIGHT;
    }

    /* Prefer digital D-Pad buttons, but settle for digital or analog hat. */
    mapped = 0;

    if (joystick->hwdata->has_key[BTN_DPAD_UP]) {
        out->dpup.kind = EMappingKind_Button;
        out->dpup.target = joystick->hwdata->key_map[BTN_DPAD_UP];
        mapped |= MAPPED_DPAD_UP;
    }

    if (joystick->hwdata->has_key[BTN_DPAD_DOWN]) {
        out->dpdown.kind = EMappingKind_Button;
        out->dpdown.target = joystick->hwdata->key_map[BTN_DPAD_DOWN];
        mapped |= MAPPED_DPAD_DOWN;
    }

    if (joystick->hwdata->has_key[BTN_DPAD_LEFT]) {
        out->dpleft.kind = EMappingKind_Button;
        out->dpleft.target = joystick->hwdata->key_map[BTN_DPAD_LEFT];
        mapped |= MAPPED_DPAD_LEFT;
    }

    if (joystick->hwdata->has_key[BTN_DPAD_RIGHT]) {
        out->dpright.kind = EMappingKind_Button;
        out->dpright.target = joystick->hwdata->key_map[BTN_DPAD_RIGHT];
        mapped |= MAPPED_DPAD_RIGHT;
    }

    if (mapped != MAPPED_DPAD_ALL) {
        if (joystick->hwdata->has_hat[0]) {
            int hat = joystick->hwdata->hats_indices[0] << 4;
            out->dpleft.kind = EMappingKind_Hat;
            out->dpright.kind = EMappingKind_Hat;
            out->dpup.kind = EMappingKind_Hat;
            out->dpdown.kind = EMappingKind_Hat;
            out->dpleft.target = hat | 0x8;
            out->dpright.target = hat | 0x2;
            out->dpup.target = hat | 0x1;
            out->dpdown.target = hat | 0x4;
            mapped |= MAPPED_DPAD_ALL;
        } else if (joystick->hwdata->has_abs[ABS_HAT0X] && joystick->hwdata->has_abs[ABS_HAT0Y]) {
            out->dpleft.kind = EMappingKind_Axis;
            out->dpright.kind = EMappingKind_Axis;
            out->dpup.kind = EMappingKind_Axis;
            out->dpdown.kind = EMappingKind_Axis;
            out->dpleft.target = joystick->hwdata->abs_map[ABS_HAT0X];
            out->dpright.target = joystick->hwdata->abs_map[ABS_HAT0X];
            out->dpup.target = joystick->hwdata->abs_map[ABS_HAT0Y];
            out->dpdown.target = joystick->hwdata->abs_map[ABS_HAT0Y];
            mapped |= MAPPED_DPAD_ALL;
        }
    }

    if (joystick->hwdata->has_abs[ABS_X] && joystick->hwdata->has_abs[ABS_Y]) {
        out->leftx.kind = EMappingKind_Axis;
        out->lefty.kind = EMappingKind_Axis;
        out->leftx.target = joystick->hwdata->abs_map[ABS_X];
        out->lefty.target = joystick->hwdata->abs_map[ABS_Y];
    }

    /* Second stick: RX/RY (Linux Gamepad Specification, Xbox 360, Playstation),
       or Z/RZ (Android convention). */
    if (joystick->hwdata->has_abs[ABS_RX] && joystick->hwdata->has_abs[ABS_RY]) {
        out->rightx.kind = EMappingKind_Axis;
        out->righty.kind = EMappingKind_Axis;
        out->rightx.target = joystick->hwdata->abs_map[ABS_RX];
        out->righty.target = joystick->hwdata->abs_map[ABS_RY];
    } else if (joystick->hwdata->has_abs[ABS_Z] && joystick->hwdata->has_abs[ABS_RZ]) {
        out->rightx.kind = EMappingKind_Axis;
        out->righty.kind = EMappingKind_Axis;
        out->rightx.target = joystick->hwdata->abs_map[ABS_Z];
        out->righty.target = joystick->hwdata->abs_map[ABS_RZ];
    }

    if (SDL_JoystickGetVendor(joystick) == USB_VENDOR_MICROSOFT) {
        /* The Xbox Elite controllers have the paddles as BTN_TRIGGER_HAPPY5 - BTN_TRIGGER_HAPPY8 */
        if (joystick->hwdata->has_key[IRIX_BTN_TRIGGER_HAPPY5] &&
            joystick->hwdata->has_key[IRIX_BTN_TRIGGER_HAPPY6] &&
            joystick->hwdata->has_key[IRIX_BTN_TRIGGER_HAPPY7] &&
            joystick->hwdata->has_key[IRIX_BTN_TRIGGER_HAPPY8]) {
            out->paddle1.kind = EMappingKind_Button;
            out->paddle1.target = joystick->hwdata->key_map[IRIX_BTN_TRIGGER_HAPPY5];
            out->paddle2.kind = EMappingKind_Button;
            out->paddle2.target = joystick->hwdata->key_map[IRIX_BTN_TRIGGER_HAPPY7];
            out->paddle3.kind = EMappingKind_Button;
            out->paddle3.target = joystick->hwdata->key_map[IRIX_BTN_TRIGGER_HAPPY6];
            out->paddle4.kind = EMappingKind_Button;
            out->paddle4.target = joystick->hwdata->key_map[IRIX_BTN_TRIGGER_HAPPY8];
        }

        /* The Xbox Series X controllers have the Share button as KEY_RECORD */
        if (joystick->hwdata->has_key[KEY_RECORD]) {
            out->misc1.kind = EMappingKind_Button;
            out->misc1.target = joystick->hwdata->key_map[KEY_RECORD];
        }
    }

    IRIX_JoystickClose(joystick);
    SDL_free(joystick);

    /* Cache the mapping for later */
    item->mapping = (SDL_GamepadMapping *)SDL_malloc(sizeof(*item->mapping));
    if (item->mapping) {
        SDL_memcpy(item->mapping, out, sizeof(*out));
    }

    return SDL_TRUE;
}

SDL_JoystickDriver SDL_IRIX_JoystickDriver = {
    IRIX_JoystickInit,
    IRIX_JoystickGetCount,
    IRIX_JoystickDetect,
    IRIX_JoystickGetDeviceName,
    IRIX_JoystickGetDevicePath,
    IRIX_JoystickGetDeviceSteamVirtualGamepadSlot,
    IRIX_JoystickGetDevicePlayerIndex,
    IRIX_JoystickSetDevicePlayerIndex,
    IRIX_JoystickGetDeviceGUID,
    IRIX_JoystickGetDeviceInstanceID,
    IRIX_JoystickOpen,
    IRIX_JoystickRumble,
    IRIX_JoystickRumbleTriggers,
    IRIX_JoystickGetCapabilities,
    IRIX_JoystickSetLED,
    IRIX_JoystickSendEffect,
    IRIX_JoystickSetSensorsEnabled,
    IRIX_JoystickUpdate,
    IRIX_JoystickClose,
    IRIX_JoystickQuit,
    IRIX_JoystickGetGamepadMapping
};

#endif /* SDL_JOYSTICK_IRIX */

/* vi: set ts=4 sw=4 expandtab: */
