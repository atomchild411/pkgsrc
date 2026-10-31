/*
htop - irix/IrixProcessTable.c
(C) 2014 Hisham H. Muhammad
Released under the GNU GPLv2+, see the COPYING file
in the source distribution for its full text.
*/

#include "config.h" // IWYU pragma: keep

#include "irix/IrixProcessTable.h"

#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <sys/procfs.h>
#include <sys/types.h>

#include "Macros.h"
#include "ProcessTable.h"
#include "XUtils.h"
#include "irix/IrixMachine.h"
#include "irix/IrixProcess.h"


ProcessTable* ProcessTable_new(Machine* host, Hashtable* pidMatchList) {
   IrixProcessTable* this = xCalloc(1, sizeof(IrixProcessTable));
   Object_setClass(this, Class(ProcessTable));

   ProcessTable* super = &this->super;
   ProcessTable_init(super, Class(IrixProcess), host, pidMatchList);

   return super;
}

void ProcessTable_delete(Object* cast) {
   IrixProcessTable* this = (IrixProcessTable*) cast;
   ProcessTable_done(&this->super);
   free(this);
}

/* pr_sname as ps(1) prints it; 'R' is both running and runnable, and
   pr_sonproc says which */
static ProcessState IrixProcessTable_getProcessState(char sname, cpuid_t onproc) {
   switch (sname) {
      case 'S': return SLEEPING;
      case 'R': return onproc >= 0 ? RUNNING : RUNNABLE;
      case 'Z': return ZOMBIE;
      case 'T': return STOPPED;
      case 'I': return IDLE;
      case 'X': return WAITING; /* SXBRK: waiting for memory */
      default:  return UNKNOWN;
   }
}

/* pr_psargs holds the first PRARGSZ bytes of the command line */
static void IrixProcessTable_updateCmdline(Process* proc, const prpsinfo_t* ps) {
   char cmdline[PRARGSZ + 1];
   String_safeStrncpy(cmdline, ps->pr_psargs, sizeof(cmdline));
   if (cmdline[0] == '\0') /* zombies keep neither, as ps(1) shows */
      String_safeStrncpy(cmdline, ps->pr_fname[0] ? ps->pr_fname : "<defunct>", sizeof(cmdline));

   size_t end = strcspn(cmdline, " ");
   size_t start = 0;
   for (size_t i = 0; i < end; i++) {
      if (cmdline[i] == '/')
         start = i + 1;
   }
   if (end == 0)
      end = strlen(cmdline);

   Process_updateCmdline(proc, cmdline, start, end);
}

void ProcessTable_goThroughEntries(ProcessTable* super) {
   const Machine* host = super->super.host;
   const IrixMachine* ihost = (const IrixMachine*) host;
   const Settings* settings = host->settings;
   uint64_t elapsedMs = host->monotonicMs - host->prevMonotonicMs;

   /* /proc/pinfo answers PIOCPSINFO for every process, whoever owns it */
   const char* base = "/proc/pinfo";
   DIR* dir = opendir(base);
   if (!dir) {
      base = "/proc";
      dir = opendir(base);
   }
   if (!dir)
      return;

   const struct dirent* entry;
   while ((entry = readdir(dir)) != NULL) {
      char* end;
      long pid = strtol(entry->d_name, &end, 10);
      if (end == entry->d_name || *end != '\0' || pid <= 0)
         continue; /* pid 0 is sched, the kernel itself */

      char path[64];
      xSnprintf(path, sizeof(path), "%s/%s", base, entry->d_name);
      int fd = open(path, O_RDONLY);
      if (fd < 0)
         continue;
      prpsinfo_t ps;
      int r = ioctl(fd, PIOCPSINFO, &ps);
      close(fd);
      if (r < 0)
         continue;

      bool preExisting;
      Process* proc = ProcessTable_getProcess(super, ps.pr_pid, &preExisting, IrixProcess_new);
      IrixProcess* ip = (IrixProcess*) proc;

      Process_setPid(proc, ps.pr_pid);
      Process_setParent(proc, ps.pr_ppid);
      Process_setThreadGroup(proc, ps.pr_pid);
      proc->pgrp = ps.pr_pgrp;
      proc->session = ps.pr_sid;
      proc->tty_nr = (ps.pr_ttydev == PRNODEV) ? 0 : (unsigned long int)ps.pr_ttydev;
      proc->priority = ps.pr_pri;
      proc->nice = ps.pr_nice - NZERO;
      proc->processor = ps.pr_sonproc >= 0 ? ps.pr_sonproc : 0;
      proc->state = IrixProcessTable_getProcessState(ps.pr_sname, ps.pr_sonproc);
      proc->nlwp = ps.pr_thds > 0 ? (long int)ps.pr_thds : 1;

      proc->m_virt = (long)ps.pr_size * (long)ihost->pageSizeKB;
      proc->m_resident = (long)ps.pr_rssize * (long)ihost->pageSizeKB;
      proc->percent_mem = host->totalMem > 0 ? proc->m_resident / (double)host->totalMem * 100.0 : 0.0;

      /* TIME is in hundredths of a second; %CPU from its growth since the last scan */
      unsigned long long int time = (unsigned long long int)ps.pr_time.tv_sec * 100
                                  + (unsigned long long int)ps.pr_time.tv_nsec / 10000000;
      if (preExisting && elapsedMs > 0 && time >= ip->lastTime) {
         proc->percent_cpu = (double)(time - ip->lastTime) * 10.0 / (double)elapsedMs * 100.0;
         proc->percent_cpu = CLAMP(proc->percent_cpu, 0.0, host->activeCPUs * 100.0);
      } else {
         proc->percent_cpu = 0.0;
      }
      Process_updateCPUFieldWidths(proc->percent_cpu);
      ip->lastTime = time;
      proc->time = time;

      if (!preExisting || proc->st_uid != ps.pr_uid) {
         proc->st_uid = ps.pr_uid;
         proc->user = UsersTable_getRef(host->usersTable, proc->st_uid);
      }

      Process_updateComm(proc, ps.pr_fname[0] ? ps.pr_fname : NULL);
      IrixProcessTable_updateCmdline(proc, &ps);

      if (!preExisting) {
         /* kernel daemons (vhand, bdflush, ...) hang off sched */
         proc->isKernelThread = ps.pr_ppid == 0 && ps.pr_pid != 1;
         proc->isUserlandThread = false;
         proc->starttime_ctime = ps.pr_start.tv_sec;
         Process_fillStarttimeBuffer(proc);
      }

      if (proc->isKernelThread) {
         super->kernelThreads++;
         super->totalTasks++;
      } else {
         super->totalTasks++;
         if (!settings->hideUserlandThreads && proc->nlwp > 1) {
            super->userlandThreads += proc->nlwp - 1;
            super->totalTasks += proc->nlwp - 1;
         }
      }
      if (proc->state == RUNNING || proc->state == RUNNABLE)
         super->runningTasks++;

      proc->super.show = !(settings->hideKernelThreads && proc->isKernelThread);
      proc->super.updated = true;

      if (!preExisting)
         ProcessTable_add(super, proc);
   }

   closedir(dir);
}
