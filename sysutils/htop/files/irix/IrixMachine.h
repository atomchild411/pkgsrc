#ifndef HEADER_IrixMachine
#define HEADER_IrixMachine
/*
htop - irix/IrixMachine.h
(C) 2014 Hisham H. Muhammad
Released under the GNU GPLv2+, see the COPYING file
in the source distribution for its full text.
*/

#include <stdbool.h>
#include <stdint.h>

#include "Machine.h"


typedef struct CPUData_ {
   double userPercent;
   double systemPercent;
   double irqPercent;
   double ioWaitPercent;
   double idlePercent;
   double systemAllPercent;

   /* clock ticks at the previous scan */
   uint64_t luser;
   uint64_t lkrnl;
   uint64_t lintr;
   uint64_t lwait;
   uint64_t lidle;

   bool online;
} CPUData;

typedef struct IrixMachine_ {
   Machine super;

   size_t pageSize;
   size_t pageSizeKB;

   memory_t usedMem;
   memory_t buffersMem;
   memory_t cachedMem;

   /* cpus[0] is the average when there is more than one CPU */
   CPUData* cpus;
} IrixMachine;

#endif
