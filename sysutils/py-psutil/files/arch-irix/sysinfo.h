/*
 * Copyright (c) 2009, Giampaolo Rodola'. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

// IRIX's kernel statistics (struct sysinfo), as plain numbers.
struct psutil_irix_si {
    unsigned long long user, kernel, idle, wait, intr, sxbrk;  // ticks
    unsigned long long pswitch, syscall, intr_svcd;
    unsigned long long bswapin, bswapout;  // 512-byte blocks
};

// cpu -1: all CPUs summed (MP_SAGET); else that CPU (MP_SAGET1).
// Returns -1 with errno set on failure.
int psutil_irix_sysinfo(int cpu, struct psutil_irix_si *out);
