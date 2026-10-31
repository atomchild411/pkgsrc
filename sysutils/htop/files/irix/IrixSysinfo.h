#ifndef HEADER_IrixSysinfo
#define HEADER_IrixSysinfo
/*
htop - irix/IrixSysinfo.h
(C) 2026 htop dev team
Released under the GNU GPLv2+, see the COPYING file
in the source distribution for its full text.
*/

/* IRIX's per-CPU clock ticks (struct sysinfo), as plain numbers */
typedef struct IrixCPUTicks_ {
   unsigned long long int user;
   unsigned long long int kernel;
   unsigned long long int idle;
   unsigned long long int wait;
   unsigned long long int intr;
   unsigned long long int sxbrk;
} IrixCPUTicks;

/* cpu -1: all CPUs summed (MP_SAGET); else that CPU (MP_SAGET1).
   Returns -1 on failure. */
int IrixSysinfo_cpuTicks(int cpu, IrixCPUTicks* out);

#endif
