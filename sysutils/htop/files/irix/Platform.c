/*
htop - irix/Platform.c
(C) 2014 Hisham H. Muhammad
(C) 2015 David C. Hunt
Released under the GNU GPLv2+, see the COPYING file
in the source distribution for its full text.
*/

#include "config.h" // IWYU pragma: keep

#include "irix/Platform.h"

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/times.h>

#include "CPUMeter.h"
#include "DateTimeMeter.h"
#include "FileDescriptorMeter.h"
#include "HostnameMeter.h"
#include "LoadAverageMeter.h"
#include "Macros.h"
#include "MemoryMeter.h"
#include "MemorySwapMeter.h"
#include "SwapMeter.h"
#include "SysArchMeter.h"
#include "TasksMeter.h"
#include "UptimeMeter.h"
#include "irix/IrixMachine.h"


const ScreenDefaults Platform_defaultScreens[] = {
   {
      .name = "Main",
      .columns = "PID USER PRIORITY NICE M_VIRT M_RESIDENT STATE PERCENT_CPU PERCENT_MEM TIME Command",
      .sortKey = "PERCENT_CPU",
   },
};

const unsigned int Platform_numberOfDefaultScreens = ARRAYSIZE(Platform_defaultScreens);

const SignalItem Platform_signals[] = {
   { .name = " 0 Cancel",      .number =  0 },
   { .name = " 1 SIGHUP",      .number =  1 },
   { .name = " 2 SIGINT",      .number =  2 },
   { .name = " 3 SIGQUIT",     .number =  3 },
   { .name = " 4 SIGILL",      .number =  4 },
   { .name = " 5 SIGTRAP",     .number =  5 },
   { .name = " 6 SIGABRT/IOT", .number =  6 },
   { .name = " 7 SIGEMT",      .number =  7 },
   { .name = " 8 SIGFPE",      .number =  8 },
   { .name = " 9 SIGKILL",     .number =  9 },
   { .name = "10 SIGBUS",      .number = 10 },
   { .name = "11 SIGSEGV",     .number = 11 },
   { .name = "12 SIGSYS",      .number = 12 },
   { .name = "13 SIGPIPE",     .number = 13 },
   { .name = "14 SIGALRM",     .number = 14 },
   { .name = "15 SIGTERM",     .number = 15 },
   { .name = "16 SIGUSR1",     .number = 16 },
   { .name = "17 SIGUSR2",     .number = 17 },
   { .name = "18 SIGCHLD/CLD", .number = 18 },
   { .name = "19 SIGPWR",      .number = 19 },
   { .name = "20 SIGWINCH",    .number = 20 },
   { .name = "21 SIGURG",      .number = 21 },
   { .name = "22 SIGPOLL/IO",  .number = 22 },
   { .name = "23 SIGSTOP",     .number = 23 },
   { .name = "24 SIGTSTP",     .number = 24 },
   { .name = "25 SIGCONT",     .number = 25 },
   { .name = "26 SIGTTIN",     .number = 26 },
   { .name = "27 SIGTTOU",     .number = 27 },
   { .name = "28 SIGVTALRM",   .number = 28 },
   { .name = "29 SIGPROF",     .number = 29 },
   { .name = "30 SIGXCPU",     .number = 30 },
   { .name = "31 SIGXFSZ",     .number = 31 },
   { .name = "33 SIGCKPT",     .number = 33 },
   { .name = "34 SIGRESTART",  .number = 34 },
};

const unsigned int Platform_numberOfSignals = ARRAYSIZE(Platform_signals);

enum {
   MEMORY_CLASS_USED = 0,
   MEMORY_CLASS_BUFFERS,
   MEMORY_CLASS_CACHED,
}; // N.B. the chart will display categories in this order

const MemoryClass Platform_memoryClasses[] = {
   [MEMORY_CLASS_USED] = { .label = "used", .countsAsUsed = true, .countsAsCache = false, .color = MEMORY_1 },
   [MEMORY_CLASS_BUFFERS] = { .label = "buffers", .countsAsUsed = false, .countsAsCache = true, .color = MEMORY_2 },
   [MEMORY_CLASS_CACHED] = { .label = "cache", .countsAsUsed = false, .countsAsCache = true, .color = MEMORY_3 },
};

const unsigned int Platform_numberOfMemoryClasses = ARRAYSIZE(Platform_memoryClasses);

const MeterClass* const Platform_meterTypes[] = {
   &CPUMeter_class,
   &ClockMeter_class,
   &DateMeter_class,
   &DateTimeMeter_class,
   &LoadAverageMeter_class,
   &LoadMeter_class,
   &MemoryMeter_class,
   &SwapMeter_class,
   &MemorySwapMeter_class,
   &TasksMeter_class,
   &HostnameMeter_class,
   &SysArchMeter_class,
   &UptimeMeter_class,
   &SecondsUptimeMeter_class,
   &AllCPUsMeter_class,
   &AllCPUs2Meter_class,
   &AllCPUs4Meter_class,
   &AllCPUs8Meter_class,
   &LeftCPUsMeter_class,
   &RightCPUsMeter_class,
   &LeftCPUs2Meter_class,
   &RightCPUs2Meter_class,
   &LeftCPUs4Meter_class,
   &RightCPUs4Meter_class,
   &LeftCPUs8Meter_class,
   &RightCPUs8Meter_class,
   &FileDescriptorMeter_class,
   &BlankMeter_class,
   NULL
};

bool Platform_init(void) {
   /* no platform-specific setup needed */
   return true;
}

void Platform_done(void) {
   /* no platform-specific cleanup needed */
}

void Platform_setBindings(Htop_Action* keys) {
   /* no platform-specific key bindings */
   (void) keys;
}

int Platform_getUptime(void) {
   /* times() counts clock ticks since boot */
   struct tms tms;
   clock_t ticks = times(&tms);
   long hz = sysconf(_SC_CLK_TCK);
   if (ticks == (clock_t)-1 || hz <= 0)
      return -1;
   return (int)((unsigned long)ticks / (unsigned long)hz);
}

void Platform_getLoadAverage(double* one, double* five, double* fifteen) {
   double loadavg[3];
   if (getloadavg(loadavg, 3) < 3) {
      *one = NAN;
      *five = NAN;
      *fifteen = NAN;
      return;
   }
   *one = loadavg[0];
   *five = loadavg[1];
   *fifteen = loadavg[2];
}

pid_t Platform_getMaxPid(void) {
   /* MAXPID */
   return 2147483647;
}

double Platform_setCPUValues(Meter* this, unsigned int cpu) {
   const Machine* host = this->host;
   const IrixMachine* ihost = (const IrixMachine*) host;
   const CPUData* cpuData = (host->existingCPUs == 1) ? &ihost->cpus[0] : &ihost->cpus[cpu];
   double* v = this->values;

   if (!cpuData->online) {
      this->curItems = 0;
      return NAN;
   }

   v[CPU_METER_NICE] = 0.0;
   v[CPU_METER_NORMAL] = cpuData->userPercent;
   if (host->settings->detailedCPUTime) {
      v[CPU_METER_KERNEL] = cpuData->systemPercent;
      v[CPU_METER_IRQ] = cpuData->irqPercent;
      v[CPU_METER_SOFTIRQ] = 0.0;
      v[CPU_METER_STEAL] = 0.0;
      v[CPU_METER_GUEST] = 0.0;
      v[CPU_METER_IOWAIT] = cpuData->ioWaitPercent;
      this->curItems = 8;
   } else {
      v[CPU_METER_KERNEL] = cpuData->systemAllPercent;
      this->curItems = 3;
   }

   double percent = sumPositiveValues(v, this->curItems);
   percent = MINIMUM(percent, 100.0);

   v[CPU_METER_FREQUENCY] = NAN;
   v[CPU_METER_TEMPERATURE] = NAN;

   return percent;
}

void Platform_setMemoryValues(Meter* this) {
   const Machine* host = this->host;
   const IrixMachine* ihost = (const IrixMachine*) host;

   this->total = host->totalMem;
   this->values[MEMORY_CLASS_USED] = ihost->usedMem;
   this->values[MEMORY_CLASS_BUFFERS] = ihost->buffersMem;
   this->values[MEMORY_CLASS_CACHED] = ihost->cachedMem;
}

void Platform_setSwapValues(Meter* this) {
   const Machine* host = this->host;

   this->total = host->totalSwap;
   this->values[SWAP_METER_USED] = host->usedSwap;
}

char* Platform_getProcessEnv(pid_t pid) {
   (void) pid;
   return NULL;
}

FileLocks_ProcessData* Platform_getProcessLocks(pid_t pid) {
   (void)pid;
   return NULL;
}

void Platform_getFileDescriptors(double* used, double* max) {
   *used = NAN;
   *max = NAN;
}

bool Platform_getDiskIO(DiskIOData* data) {
   (void)data;
   return false;
}

bool Platform_getNetworkIO(NetworkIOData* data) {
   (void)data;
   return false;
}

void Platform_getBattery(double* percent, ACPresence* isOnAC) {
   *percent = NAN;
   *isOnAC = AC_ERROR;
}
