/*
  SDL audio on IRIX: the Audio Library (libaudio, <dmedia/audio.h>).
*/
#include "../../SDL_internal.h"

#ifndef SDL_irixaudio_h_
#define SDL_irixaudio_h_

#include "../SDL_sysaudio.h"

/* Hidden "this" pointer for the audio functions */
#define _THIS SDL_AudioDevice *this

struct SDL_PrivateAudioData
{
    void *port;     /* the Audio Library's ALport */
    Uint8 *mixbuf;  /* SDL mixes a period here */
    int frames;     /* sample frames in a period */
};

#endif /* SDL_irixaudio_h_ */

/* vi: set ts=4 sw=4 expandtab: */
