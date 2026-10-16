/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * IRIX 6.5 (n32), pthreads only.  NSPR dropped its old IRIX port; this
 * one follows the NetBSD pthreads port.  IRIX has no IPv6 networking, so
 * _PR_INET6 stays undefined (and with it NSPR's getaddrinfo path: lookups
 * go through gethostbyname_r).
 */

#ifndef nspr_irix_defs_h___
#define nspr_irix_defs_h___

#ifndef _PR_PTHREADS
#error "IRIX supports only the pthreads build of NSPR"
#endif

#define PR_LINKER_ARCH      "irix"
#define _PR_SI_SYSNAME      "IRIX"
#define _PR_SI_ARCHITECTURE "mips"
#define PR_DLL_SUFFIX       ".so"

#define _PR_VMBASE              0x30000000
#define _PR_STACK_VMBASE        0x50000000
#define _MD_DEFAULT_STACK_SIZE  65536L
#define _MD_MMAP_FLAGS          MAP_PRIVATE

#undef  HAVE_STACK_GROWING_UP
#define HAVE_DLL
#define USE_DLFCN
#define _PR_HAVE_LARGE_OFF_T
#define _PR_STAT_HAS_ONLY_ST_ATIME
#define _PR_POLL_AVAILABLE
#define _PR_USE_POLL
#define _PR_HAVE_SYSV_SEMAPHORES
#define PR_HAVE_SYSV_NAMED_SHARED_MEMORY
#define _PR_HAVE_INET_NTOP

#define USE_SETJMP

extern void _MD_EarlyInit(void);

#define _MD_EARLY_INIT          _MD_EarlyInit
#define _MD_FINAL_INIT          _PR_UnixInit
#define _PR_HAVE_CLOCK_MONOTONIC

#define _MD_SELECT              select
#if defined(_PR_POLL_AVAILABLE)
#include <poll.h>
#define _MD_POLL                poll
#endif

#endif /* nspr_irix_defs_h___ */
