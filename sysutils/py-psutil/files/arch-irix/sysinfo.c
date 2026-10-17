/*
 * Copyright (c) 2009, Giampaolo Rodola'. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 *
 * IRIX's struct sysinfo, read here without <Python.h>: Python selects the
 * X/Open compilation mode, in which <sys/sysinfo.h> (kernel statistics,
 * with SGI types) is not available.
 */

#include <sys/types.h>
#include <sys/sysmp.h>
#include <sys/sysinfo.h>

#include "sysinfo.h"

int
psutil_irix_sysinfo(int cpu, struct psutil_irix_si *out) {
    struct sysinfo si;
    int ret;

    if (cpu < 0)
        ret = sysmp(MP_SAGET, MPSA_SINFO, &si, sizeof(si));
    else
        ret = sysmp(MP_SAGET1, MPSA_SINFO, &si, sizeof(si), cpu);
    if (ret == -1)
        return -1;
    out->user = si.cpu[CPU_USER];
    out->kernel = si.cpu[CPU_KERNEL];
    out->idle = si.cpu[CPU_IDLE];
    out->wait = si.cpu[CPU_WAIT];
    out->intr = si.cpu[CPU_INTR];
    out->sxbrk = si.cpu[CPU_SXBRK];
    out->pswitch = si.pswitch;
    out->syscall = si.syscall;
    out->intr_svcd = si.intr_svcd;
    out->bswapin = si.bswapin;
    out->bswapout = si.bswapout;
    return 0;
}
