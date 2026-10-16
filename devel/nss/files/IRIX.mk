#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# IRIX 6.5 (n32, pthreads), modelled on NetBSD.mk; NSS dropped its old
# IRIX support.

include $(CORE_DEPTH)/coreconf/UNIX.mk

CC			?= cc
CXX			?= c++
DEFAULT_COMPILER	= ${CC}
CCC			= ${CXX}
RANLIB			= ranlib

CPU_ARCH		?= mips

DLL_SUFFIX		= so

OS_CFLAGS		= $(DSO_CFLAGS) $(OS_REL_CFLAGS) -Wall -Wno-switch -DIRIX -Dunix -DHAVE_STRERROR

ARCH			= irix

# For the host tools (nsinstall) when cross building on glibc, which hides
# strdup and fchown under -std=c99; IRIX's headers ignore it.
DEFINES			+= -D_DEFAULT_SOURCE

DSO_CFLAGS		= -fPIC -DPIC
DSO_LDOPTS		= -shared -Wl,-soname,lib$(LIBRARY_NAME)$(LIBRARY_VERSION).$(DLL_SUFFIX)

ifndef CLASSIC_NSPR
USE_PTHREADS		= 1
DEFINES			+= -D_THREAD_SAFE -D_REENTRANT
OS_LIBS			+= -lpthread
DSO_LDOPTS		+= -lpthread
endif

ifdef LIBRUNPATH
DSO_LDOPTS		+= -Wl,-R$(LIBRUNPATH)
endif

MKSHLIB			= $(CC) $(DSO_LDOPTS)
ifdef MAPFILE
	MKSHLIB += -Wl,--version-script,$(MAPFILE)
endif
PROCESS_MAP_FILE = grep -v ';-' $< | \
        sed -e 's,;+,,' -e 's; DATA ;;' -e 's,;;,,' -e 's,;.*,;,' > $@
