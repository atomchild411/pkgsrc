# $NetBSD$
#
# Cross-compiler toolchain for IRIX 6.5 (n32).  Modelled on
# cross.NetBSD.mk: TOOLDIR/bin holds the target tools under their GNU
# platform prefix (${MACHINE_GNU_PLATFORM}-ar, -nm, -ranlib, -strip, ...),
# so that GNU configure scripts run with --host=${MACHINE_GNU_PLATFORM}
# find them, and pkgsrc's own AR/RANLIB/STRIP point at them too.
#
# The C/C++ compilers come from PKGSRC_COMPILER=clang with CLANGBASE set to
# a clang whose default target is IRIX (see mk.conf); CC/CXX here only name
# the prefixed drivers so that the wrappers are also installed under those
# names.

TOOLS_PLATFORM.readelf?=	${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-readelf
TOOLS_PLATFORM.strip?=		${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-strip

.for _t_ in ar as ld nm objcopy objdump ranlib readelf strip
.  if exists(${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-${_t_})
TOOLS_PATH.${MACHINE_GNU_PLATFORM}-${_t_}?=	\
	${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-${_t_}
TOOLS_CREATE+=	${MACHINE_GNU_PLATFORM}-${_t_}
.  endif
.endfor

TOOLS_PATH.ar?=		${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-ar
TOOLS_CREATE+=		ar
TOOLS_PATH.nm?=		${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-nm
TOOLS_CREATE+=		nm
TOOLS_PATH.ranlib?=	${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-ranlib
TOOLS_CREATE+=		ranlib
TOOLS_PATH.readelf?=	${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-readelf
TOOLS_CREATE+=		readelf

CC=		${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-clang
CXX=		${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-clang++
LD=		${TOOLDIR}/bin/${MACHINE_GNU_PLATFORM}-ld

# Where the tools are on the TARGET, for what runs there: +INSTALL and
# +DEINSTALL, other FILES_SUBST-processed files (bsd.pkginstall.mk), and
# the #! lines REPLACE_SH/_KSH/_AWK write (replace-interpreter.mk).  The
# system paths are tools.IRIX.mk's; the rest are pkgsrc's own.
TARGET_TOOLS=		AWK BASENAME CAT CHGRP CHMOD CHOWN CMP CP CSH CUT DATE \
			DIFF DIRNAME ECHO EGREP EXPR FALSE FGREP FILE_CMD FIND \
			GREP GTAR GUNZIP_CMD GZCAT GZIP_CMD HEAD HOSTNAME_CMD \
			ID INSTALL_INFO KSH LINKFARM LN LS M4 MAIL_CMD MKDIR MV \
			NICE PERL5 PRINTF PWD_CMD RCD_SCRIPTS_SHELL RM RMDIR \
			SED SETENV SH SLEEP SORT SU TAIL TEE TEST TOUCH TR TRUE \
			TSORT UNIQ WC XARGS
TARGET_TOOL.AWK=	/usr/bin/nawk
TARGET_TOOL.BASENAME=	/sbin/basename
TARGET_TOOL.CAT=	/sbin/cat
TARGET_TOOL.CHGRP=	/sbin/chgrp
TARGET_TOOL.CHMOD=	/sbin/chmod
TARGET_TOOL.CHOWN=	/sbin/chown
TARGET_TOOL.CMP=	/usr/bin/cmp
TARGET_TOOL.CP=		/sbin/cp
TARGET_TOOL.CSH=	/bin/csh
TARGET_TOOL.CUT=	/usr/bin/cut
TARGET_TOOL.DATE=	/sbin/date
TARGET_TOOL.DIFF=	/usr/bin/diff
TARGET_TOOL.DIRNAME=	/usr/bin/dirname
TARGET_TOOL.ECHO=	echo
TARGET_TOOL.EGREP=	/usr/bin/egrep
TARGET_TOOL.EXPR=	/bin/expr
TARGET_TOOL.FALSE=	false
TARGET_TOOL.FGREP=	/usr/bin/fgrep
TARGET_TOOL.FILE_CMD=	/usr/bin/file
TARGET_TOOL.FIND=	/sbin/find
TARGET_TOOL.GREP=	/sbin/grep
TARGET_TOOL.GTAR=	${LOCALBASE}/bin/gtar
TARGET_TOOL.GUNZIP_CMD=	/usr/sbin/gunzip -f
TARGET_TOOL.GZCAT=	/usr/sbin/gzcat
TARGET_TOOL.GZIP_CMD=	/usr/sbin/gzip -nf
TARGET_TOOL.HEAD=	/usr/bsd/head
TARGET_TOOL.HOSTNAME_CMD=	/usr/bsd/hostname
TARGET_TOOL.ID=		/usr/bin/id
TARGET_TOOL.INSTALL_INFO=	${LOCALBASE}/bin/pkg_install-info
TARGET_TOOL.KSH=	/bin/ksh
TARGET_TOOL.LINKFARM=	${LOCALBASE}/sbin/linkfarm
TARGET_TOOL.LN=		/sbin/ln
TARGET_TOOL.LS=		/sbin/ls
TARGET_TOOL.M4=		/sbin/m4
TARGET_TOOL.MAIL_CMD=	/usr/sbin/mailx
TARGET_TOOL.MKDIR=	/sbin/mkdir -p
TARGET_TOOL.MV=		/sbin/mv
TARGET_TOOL.NICE=	/sbin/nice
TARGET_TOOL.PERL5=	${LOCALBASE}/bin/perl
TARGET_TOOL.PRINTF=	/usr/bin/printf
TARGET_TOOL.PWD_CMD=	/sbin/pwd
TARGET_TOOL.RCD_SCRIPTS_SHELL=	/bin/sh
TARGET_TOOL.RM=		/sbin/rm
TARGET_TOOL.RMDIR=	/usr/bin/rmdir
TARGET_TOOL.SED=	/sbin/sed
TARGET_TOOL.SETENV=	/sbin/env
TARGET_TOOL.SH=		/bin/sh
TARGET_TOOL.SLEEP=	/sbin/sleep
TARGET_TOOL.SORT=	/usr/bin/sort
TARGET_TOOL.SU=		/sbin/su
TARGET_TOOL.TAIL=	/usr/bin/tail
TARGET_TOOL.TEE=	/usr/bin/tee
TARGET_TOOL.TEST=	test
TARGET_TOOL.TOUCH=	/usr/bin/touch
TARGET_TOOL.TR=		/usr/bin/tr
TARGET_TOOL.TRUE=	true
TARGET_TOOL.TSORT=	/usr/bin/tsort
TARGET_TOOL.UNIQ=	/usr/bin/uniq
TARGET_TOOL.WC=		/sbin/wc
TARGET_TOOL.XARGS=	/sbin/xargs
