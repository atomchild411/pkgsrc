/*
htop - irix/IrixSysinfo.c
(C) 2026 htop dev team
Released under the GNU GPLv2+, see the COPYING file
in the source distribution for its full text.
*/

/* No config.h here, and SGI mode instead of the X/Open one htop asks for
   on the command line (-D_XOPEN_SOURCE=600): in that mode IRIX's
   <sys/sysinfo.h> (kernel statistics, with SGI types) is hidden. */
#undef _XOPEN_SOURCE
#undef _XOPEN_SOURCE_EXTENDED
#undef _POSIX_C_SOURCE
#undef _POSIX_SOURCE
#ifndef _SGI_SOURCE
#define _SGI_SOURCE 1
#endif

#include <sys/types.h>
#include <sys/sysmp.h>
#include <sys/sysinfo.h>

#include "irix/IrixSysinfo.h"


int IrixSysinfo_cpuTicks(int cpu, IrixCPUTicks* out) {
   struct sysinfo si;
   int ret;

   if (cpu < 0)
      ret = sysmp(MP_SAGET, MPSA_SINFO, (char*)&si, (int)sizeof(si));
   else
      ret = sysmp(MP_SAGET1, MPSA_SINFO, (char*)&si, (int)sizeof(si), cpu);
   if (ret == -1)
      return -1;

   out->user = (unsigned long)si.cpu[CPU_USER];
   out->kernel = (unsigned long)si.cpu[CPU_KERNEL];
   out->idle = (unsigned long)si.cpu[CPU_IDLE];
   out->wait = (unsigned long)si.cpu[CPU_WAIT];
   out->intr = (unsigned long)si.cpu[CPU_INTR];
   out->sxbrk = (unsigned long)si.cpu[CPU_SXBRK];
   return 0;
}
