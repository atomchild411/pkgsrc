/*
 * <revenir/input.h>: game controllers under revenir.
 *
 * IRIX has no game controller devices. Under revenir, /dev/input/eventN
 * is the host's Nth gamepad (0 first; keyboards, mice, touchpads and
 * motion sensors are never there), as Linux's input event devices (evdev)
 * are: this header has what a program needs of Linux's <linux/input.h>,
 * in IRIX's ABIs (n32, o32, n64), under Linux's names.
 *
 *   - open("/dev/input/eventN", O_RDWR or O_RDONLY [| O_NONBLOCK]):
 *     ENOENT when there is no Nth gamepad. Numbers are not kept for a
 *     gamepad: the host's are counted again at each open. To find the
 *     gamepads, open 0, 1, ... until ENOENT; to notice new ones, do that
 *     again now and then.
 *   - read: whole struct input_events (EINVAL for a buffer smaller than
 *     one); EAGAIN with O_NONBLOCK and none waiting; ENODEV once the
 *     gamepad is gone. poll and select work.
 *   - write: struct input_events of type EV_FF, to play (value 1) or
 *     stop (0) an effect uploaded with EVIOCSFF, or set FF_GAIN.
 *   - ioctl: the EVIOC* requests below. Bitmaps come as arrays of
 *     unsigned long, bit k of the map being bit (k % BITS_PER_LONG) of
 *     word (k / BITS_PER_LONG), as test_bit() below reads them.
 *   - EVIOCSFF: periodic effects with FF_CUSTOM waveforms are refused
 *     (EINVAL); the others go to the host's driver.
 *
 * Not an SGI interface: programs for IRIX on SGI hardware never find
 * these devices (open gives ENOENT there, as /dev/input does not exist).
 */
#ifndef _REVENIR_INPUT_H
#define _REVENIR_INPUT_H

#include <sys/types.h>
#include <sys/time.h>

/* IRIX's ioctl encoding (sys/ioccom.h), with a 13-bit size. */
#define _REVENIR_IOC_VOID	0x20000000
#define _REVENIR_IOC_OUT	0x40000000
#define _REVENIR_IOC_IN		0x80000000
#define _REVENIR_IOC(dir, nr, size) \
	((dir) | (((size) & 0x1fff) << 16) | ('E' << 8) | (nr))
#define _REVENIR_IOR(nr, size)	_REVENIR_IOC(_REVENIR_IOC_OUT, (nr), (size))
#define _REVENIR_IOW(nr, size)	_REVENIR_IOC(_REVENIR_IOC_IN, (nr), (size))

struct input_event {
	struct timeval time;
	unsigned short type;
	unsigned short code;
	int value;
};

struct input_id {
	unsigned short bustype;
	unsigned short vendor;
	unsigned short product;
	unsigned short version;
};

struct input_absinfo {
	int value;
	int minimum;
	int maximum;
	int fuzz;
	int flat;
	int resolution;
};

/* Force feedback. */
struct ff_replay {
	unsigned short length;
	unsigned short delay;
};

struct ff_trigger {
	unsigned short button;
	unsigned short interval;
};

struct ff_envelope {
	unsigned short attack_length;
	unsigned short attack_level;
	unsigned short fade_length;
	unsigned short fade_level;
};

struct ff_constant_effect {
	short level;
	struct ff_envelope envelope;
};

struct ff_ramp_effect {
	short start_level;
	short end_level;
	struct ff_envelope envelope;
};

struct ff_condition_effect {
	unsigned short right_saturation;
	unsigned short left_saturation;
	short right_coeff;
	short left_coeff;
	unsigned short deadband;
	short center;
};

struct ff_periodic_effect {
	unsigned short waveform;
	unsigned short period;
	short magnitude;
	short offset;
	unsigned short phase;
	struct ff_envelope envelope;
	unsigned int custom_len;
	short *custom_data;
};

struct ff_rumble_effect {
	unsigned short strong_magnitude;
	unsigned short weak_magnitude;
};

struct ff_effect {
	unsigned short type;
	short id;
	unsigned short direction;
	struct ff_trigger trigger;
	struct ff_replay replay;
	union {
		struct ff_constant_effect constant;
		struct ff_ramp_effect ramp;
		struct ff_periodic_effect periodic;
		struct ff_condition_effect condition[2];
		struct ff_rumble_effect rumble;
	} u;
};

#define EV_VERSION		0x010001

#define EVIOCGVERSION		_REVENIR_IOR(0x01, sizeof(int))
#define EVIOCGID		_REVENIR_IOR(0x02, sizeof(struct input_id))
#define EVIOCGREP		_REVENIR_IOR(0x03, 2 * sizeof(unsigned int))
#define EVIOCGNAME(len)		_REVENIR_IOR(0x06, (len))
#define EVIOCGPHYS(len)		_REVENIR_IOR(0x07, (len))
#define EVIOCGUNIQ(len)		_REVENIR_IOR(0x08, (len))
#define EVIOCGPROP(len)		_REVENIR_IOR(0x09, (len))
#define EVIOCGKEY(len)		_REVENIR_IOR(0x18, (len))
#define EVIOCGLED(len)		_REVENIR_IOR(0x19, (len))
#define EVIOCGSND(len)		_REVENIR_IOR(0x1a, (len))
#define EVIOCGSW(len)		_REVENIR_IOR(0x1b, (len))
#define EVIOCGBIT(ev, len)	_REVENIR_IOR(0x20 + (ev), (len))
#define EVIOCGABS(abs)		_REVENIR_IOR(0x40 + (abs), sizeof(struct input_absinfo))
#define EVIOCSFF		_REVENIR_IOW(0x80, sizeof(struct ff_effect))
#define EVIOCRMFF		_REVENIR_IOW(0x81, sizeof(int))
#define EVIOCGEFFECTS		_REVENIR_IOR(0x84, sizeof(int))
#define EVIOCGRAB		_REVENIR_IOW(0x90, sizeof(int))
#define EVIOCREVOKE		_REVENIR_IOW(0x91, sizeof(int))
#define EVIOCSCLOCKID		_REVENIR_IOW(0xa0, sizeof(int))

/* Bitmaps. */
#define BITS_PER_LONG		(sizeof(unsigned long) * 8)
#define NBITS(x)		((((x) - 1) / BITS_PER_LONG) + 1)
#define test_bit(nr, addr) \
	(((addr)[(nr) / BITS_PER_LONG] >> ((nr) % BITS_PER_LONG)) & 1UL)

/* Properties. */
#define INPUT_PROP_POINTER		0x00
#define INPUT_PROP_DIRECT		0x01
#define INPUT_PROP_BUTTONPAD		0x02
#define INPUT_PROP_ACCELEROMETER	0x06
#define INPUT_PROP_MAX			0x1f

/* Event types. */
#define EV_SYN			0x00
#define EV_KEY			0x01
#define EV_REL			0x02
#define EV_ABS			0x03
#define EV_MSC			0x04
#define EV_SW			0x05
#define EV_LED			0x11
#define EV_SND			0x12
#define EV_REP			0x14
#define EV_FF			0x15
#define EV_PWR			0x16
#define EV_FF_STATUS		0x17
#define EV_MAX			0x1f

#define SYN_REPORT		0
#define SYN_CONFIG		1
#define SYN_MT_REPORT		2
#define SYN_DROPPED		3

/* Buttons (EV_KEY): the codes game controllers use. */
#define BTN_MISC		0x100
#define BTN_0			0x100
#define BTN_9			0x109
#define BTN_MOUSE		0x110
#define BTN_LEFT		0x110
#define BTN_RIGHT		0x111
#define BTN_MIDDLE		0x112
#define BTN_JOYSTICK		0x120
#define BTN_TRIGGER		0x120
#define BTN_THUMB		0x121
#define BTN_THUMB2		0x122
#define BTN_TOP			0x123
#define BTN_TOP2		0x124
#define BTN_PINKIE		0x125
#define BTN_BASE		0x126
#define BTN_BASE2		0x127
#define BTN_BASE3		0x128
#define BTN_BASE4		0x129
#define BTN_BASE5		0x12a
#define BTN_BASE6		0x12b
#define BTN_DEAD		0x12f
#define BTN_GAMEPAD		0x130
#define BTN_SOUTH		0x130
#define BTN_A			0x130
#define BTN_EAST		0x131
#define BTN_B			0x131
#define BTN_C			0x132
#define BTN_NORTH		0x133
#define BTN_X			0x133
#define BTN_WEST		0x134
#define BTN_Y			0x134
#define BTN_Z			0x135
#define BTN_TL			0x136
#define BTN_TR			0x137
#define BTN_TL2			0x138
#define BTN_TR2			0x139
#define BTN_SELECT		0x13a
#define BTN_START		0x13b
#define BTN_MODE		0x13c
#define BTN_THUMBL		0x13d
#define BTN_THUMBR		0x13e
#define BTN_DIGI		0x140
#define BTN_TOUCH		0x14a
#define BTN_DPAD_UP		0x220
#define BTN_DPAD_DOWN		0x221
#define BTN_DPAD_LEFT		0x222
#define BTN_DPAD_RIGHT		0x223
#define BTN_TRIGGER_HAPPY	0x2c0
#define BTN_TRIGGER_HAPPY1	0x2c0
#define BTN_TRIGGER_HAPPY40	0x2e7
#define KEY_MAX			0x2ff
#define KEY_CNT			(KEY_MAX + 1)

/* Relative axes (EV_REL). */
#define REL_X			0x00
#define REL_Y			0x01
#define REL_Z			0x02
#define REL_WHEEL		0x08
#define REL_MAX			0x0f
#define REL_CNT			(REL_MAX + 1)

/* Absolute axes (EV_ABS). */
#define ABS_X			0x00
#define ABS_Y			0x01
#define ABS_Z			0x02
#define ABS_RX			0x03
#define ABS_RY			0x04
#define ABS_RZ			0x05
#define ABS_THROTTLE		0x06
#define ABS_RUDDER		0x07
#define ABS_WHEEL		0x08
#define ABS_GAS			0x09
#define ABS_BRAKE		0x0a
#define ABS_HAT0X		0x10
#define ABS_HAT0Y		0x11
#define ABS_HAT1X		0x12
#define ABS_HAT1Y		0x13
#define ABS_HAT2X		0x14
#define ABS_HAT2Y		0x15
#define ABS_HAT3X		0x16
#define ABS_HAT3Y		0x17
#define ABS_PRESSURE		0x18
#define ABS_DISTANCE		0x19
#define ABS_TILT_X		0x1a
#define ABS_TILT_Y		0x1b
#define ABS_TOOL_WIDTH		0x1c
#define ABS_VOLUME		0x20
#define ABS_MISC		0x28
#define ABS_MT_SLOT		0x2f
#define ABS_MAX			0x3f
#define ABS_CNT			(ABS_MAX + 1)

/* Miscellaneous (EV_MSC). */
#define MSC_SERIAL		0x00
#define MSC_SCAN		0x04
#define MSC_TIMESTAMP		0x05
#define MSC_MAX			0x07

/* LEDs (EV_LED). */
#define LED_MAX			0x0f

/* Buses (struct input_id). */
#define BUS_PCI			0x01
#define BUS_USB			0x03
#define BUS_HIL			0x04
#define BUS_BLUETOOTH		0x05
#define BUS_VIRTUAL		0x06
#define BUS_I2C			0x18
#define BUS_HOST		0x19

/* Force feedback (EV_FF, EVIOCSFF). */
#define FF_STATUS_STOPPED	0x00
#define FF_STATUS_PLAYING	0x01
#define FF_RUMBLE		0x50
#define FF_PERIODIC		0x51
#define FF_CONSTANT		0x52
#define FF_SPRING		0x53
#define FF_FRICTION		0x54
#define FF_DAMPER		0x55
#define FF_INERTIA		0x56
#define FF_RAMP			0x57
#define FF_EFFECT_MIN		FF_RUMBLE
#define FF_EFFECT_MAX		FF_RAMP
#define FF_SQUARE		0x58
#define FF_TRIANGLE		0x59
#define FF_SINE			0x5a
#define FF_SAW_UP		0x5b
#define FF_SAW_DOWN		0x5c
#define FF_CUSTOM		0x5d
#define FF_WAVEFORM_MIN		FF_SQUARE
#define FF_WAVEFORM_MAX		FF_CUSTOM
#define FF_GAIN			0x60
#define FF_AUTOCENTER		0x61
#define FF_MAX_EFFECTS		FF_GAIN
#define FF_MAX			0x7f
#define FF_CNT			(FF_MAX + 1)

#endif /* _REVENIR_INPUT_H */
