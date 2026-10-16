/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "primpl.h"

#include <signal.h>

void _MD_EarlyInit(void) {
  /*
   * Ignore FPE because coercion of a NaN to an int causes SIGFPE
   * to be raised.
   */
  struct sigaction act;

  act.sa_handler = SIG_IGN;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  sigaction(SIGFPE, &act, 0);
}

PRWord* _MD_HomeGCRegisters(PRThread* t, int isCurrent, int* np) {
  *np = 0;
  return NULL;
}
