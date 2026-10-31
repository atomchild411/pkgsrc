#ifndef HEADER_IrixProcess
#define HEADER_IrixProcess
/*
htop - irix/IrixProcess.h
(C) 2015 Hisham H. Muhammad
Released under the GNU GPLv2+, see the COPYING file
in the source distribution for its full text.
*/

#include "Machine.h"
#include "Process.h"


typedef struct IrixProcess_ {
   Process super;

   /* CPU time (hundredths of a second) at the previous scan, for %CPU */
   unsigned long long int lastTime;
} IrixProcess;

extern const ProcessFieldData Process_fields[LAST_PROCESSFIELD];

Process* IrixProcess_new(const Machine* host);

void Process_delete(Object* cast);

extern const ProcessClass IrixProcess_class;

#endif
