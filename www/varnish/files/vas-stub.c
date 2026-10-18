/* $NetBSD$ */
/*
 * VAS_Fail() for the generators built for the build machine when
 * cross-compiling (the real one is in libvarnish, built for the target).
 */
#include <stdio.h>
#include <stdlib.h>
#include "vdef.h"
#include "vas.h"

void
VAS_Fail(const char *func, const char *file, int line, const char *cond,
    enum vas_e kind)
{
	(void)kind;
	fprintf(stderr, "%s:%d: %s: assertion failed: %s\n", file, line,
	    func, cond);
	abort();
}
