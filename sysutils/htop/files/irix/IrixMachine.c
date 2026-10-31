/*
htop - irix/IrixMachine.c
(C) 2014 Hisham H. Muhammad
Released under the GNU GPLv2+, see the COPYING file
in the source distribution for its full text.
*/

#include "config.h" // IWYU pragma: keep

#include "irix/IrixMachine.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/swap.h>
#include <sys/sysmp.h>

#include "CRT.h"
#include "Macros.h"
#include "XUtils.h"
#include "irix/IrixSysinfo.h"


static void IrixMachine_updateCPUcount(IrixMachine* this) {
   Machine* super = &this->super;

   int existing = sysmp(MP_NPROCS);
   if (existing < 1)
      existing = 1;
   int active = sysmp(MP_NAPROCS);
   if (active < 1)
      active = existing;

   if ((unsigned int)existing != super->existingCPUs) {
      unsigned int n = existing == 1 ? 1 : (unsigned int)existing + 1;
      this->cpus = xReallocArray(this->cpus, n, sizeof(CPUData));
      memset(this->cpus, 0, n * sizeof(CPUData));
      this->cpus[0].online = true; /* the average is always "online" */
      super->existingCPUs = existing;
   }
   super->activeCPUs = active;
}

static void IrixMachine_cpuPercents(CPUData* cpu, const IrixCPUTicks* t) {
   uint64_t user = t->user;
   uint64_t krnl = t->kernel + t->sxbrk;
   uint64_t intr = t->intr;
   uint64_t wait = t->wait;
   uint64_t idle = t->idle;

   double total = (double)((user - cpu->luser) + (krnl - cpu->lkrnl) + (intr - cpu->lintr)
                         + (wait - cpu->lwait) + (idle - cpu->lidle));
   if (total > 0) {
      cpu->userPercent   = (user - cpu->luser) / total * 100.0;
      cpu->systemPercent = (krnl - cpu->lkrnl) / total * 100.0;
      cpu->irqPercent    = (intr - cpu->lintr) / total * 100.0;
      cpu->ioWaitPercent = (wait - cpu->lwait) / total * 100.0;
      cpu->idlePercent   = (idle - cpu->lidle) / total * 100.0;
   } else {
      cpu->userPercent = cpu->systemPercent = cpu->irqPercent = cpu->ioWaitPercent = 0.0;
      cpu->idlePercent = 100.0;
   }
   cpu->systemAllPercent = cpu->systemPercent + cpu->irqPercent;

   cpu->luser = user;
   cpu->lkrnl = krnl;
   cpu->lintr = intr;
   cpu->lwait = wait;
   cpu->lidle = idle;
}

static void IrixMachine_scanCPUTime(IrixMachine* this) {
   const Machine* super = &this->super;
   unsigned int existing = super->existingCPUs;
   IrixCPUTicks t;

   /* cpus[0] is the system-wide figure, which IRIX sums for us */
   if (IrixSysinfo_cpuTicks(-1, &t) == 0)
      IrixMachine_cpuPercents(&this->cpus[0], &t);

   if (existing == 1)
      return;

   for (unsigned int i = 0; i < existing; i++) {
      CPUData* cpu = &this->cpus[i + 1];
      if (IrixSysinfo_cpuTicks((int)i, &t) != 0) {
         cpu->online = false;
         continue;
      }
      cpu->online = true;
      IrixMachine_cpuPercents(cpu, &t);
   }
}

static void IrixMachine_scanMemoryInfo(IrixMachine* this) {
   Machine* super = &this->super;
   struct rminfo rmi;

   if (sysmp(MP_SAGET, MPSA_RMINFO, (char*)&rmi, (int)sizeof(rmi)) == 0) {
      memory_t physmem = rmi.physmem;
      memory_t freemem = MINIMUM((memory_t)rmi.freemem, physmem);
      memory_t emptymem = MINIMUM((memory_t)rmi.emptymem, freemem);
      memory_t bufmem = MINIMUM((memory_t)rmi.bufmem, physmem - freemem);

      super->totalMem = physmem * this->pageSizeKB;
      /* IRIX counts free pages that still hold file data as free; show them as cache */
      this->cachedMem = (freemem - emptymem) * this->pageSizeKB;
      this->buffersMem = bufmem * this->pageSizeKB;
      this->usedMem = (physmem - freemem - bufmem) * this->pageSizeKB;
   } else {
      super->totalMem = (memory_t)sysconf(_SC_PHYS_PAGES) * this->pageSizeKB;
      this->usedMem = 0;
      this->buffersMem = 0;
      this->cachedMem = 0;
   }

   /* swapctl counts 512-byte blocks */
   off_t total = 0;
   off_t avail = 0;
   if (swapctl(SC_GETSWAPTOT, &total) == 0 && swapctl(SC_GETFREESWAP, &avail) == 0 && total > 0) {
      super->totalSwap = (memory_t)total / 2;
      super->usedSwap = (memory_t)(total - MINIMUM(avail, total)) / 2;
   } else {
      super->totalSwap = 0;
      super->usedSwap = 0;
   }
   super->cachedSwap = 0;
}

void Machine_scan(Machine* super) {
   IrixMachine* this = (IrixMachine*) super;

   IrixMachine_updateCPUcount(this);
   IrixMachine_scanCPUTime(this);
   IrixMachine_scanMemoryInfo(this);
}

Machine* Machine_new(UsersTable* usersTable, uid_t userId) {
   IrixMachine* this = xCalloc(1, sizeof(IrixMachine));
   Machine* super = &this->super;

   Machine_init(super, usersTable, userId);

   long pageSize = sysconf(_SC_PAGESIZE);
   if (pageSize <= 0)
      pageSize = getpagesize();
   this->pageSize = (size_t)pageSize;
   this->pageSizeKB = this->pageSize / ONE_K;

   IrixMachine_updateCPUcount(this);
   IrixMachine_scanCPUTime(this);

   return super;
}

void Machine_delete(Machine* super) {
   IrixMachine* this = (IrixMachine*) super;

   Machine_done(super);
   free(this->cpus);
   free(this);
}

bool Machine_isCPUonline(const Machine* super, unsigned int id) {
   assert(id < super->existingCPUs);

   const IrixMachine* this = (const IrixMachine*) super;

   return (super->existingCPUs == 1) ? true : this->cpus[id + 1].online;
}

int Machine_getCPUPhysicalCoreID(const Machine* host, unsigned int id) {
   assert(id < host->existingCPUs);
   (void) host;
   return (int)id;
}

int Machine_getCPUThreadIndex(const Machine* host, unsigned int id) {
   assert(id < host->existingCPUs);
   (void) host; (void) id;
   return 0;
}
