# $NetBSD: Makefile,v 1.27 2019/11/02 16:16:18 rillig Exp $

DISTNAME=	dcdflib.c-1.1
PKGREVISION=	3
CATEGORIES=	math
MASTER_SITES=	# ftp://odin.mdacc.tmc.edu/pub/source/

MAINTAINER=	pkgsrc-users@NetBSD.org
#HOMEPAGE=	http://odin.mdacc.tmc.edu/anonftp/
COMMENT=	Library of C Routines for Cumulative Distribution Functions

WRKSRC=			${WRKDIR}/dcdflib.c
BUILD_DIRS=		src
DIST_SUBDIR=		${PKGNAME_NOREV}
CWARNFLAGS.clang=	-Wno-error=logical-op-parentheses
MAKE_ENV+=		LIBOWN=${LIBOWN:Q} LIBGRP=${LIBGRP:Q} \
		CWARNFLAGS.clang=${CWARNFLAGS.clang:Q}
USE_BSD_MAKEFILE=	yes

INSTALLATION_DIRS=	include lib share/doc/dcdflib.c
MAKE_FLAGS+=		MKPROFILE=yes

post-install:
	${INSTALL_DATA} ${WRKSRC}/doc/dcdflib.h ${DESTDIR}${PREFIX}/include
	cd ${WRKSRC} && ${INSTALL_DATA} README doc/dcdflib.chs		\
		doc/dcdflib.fdoc ${DESTDIR}${PREFIX}/share/doc/dcdflib.c/

.include "../../mk/bsd.prefs.mk"

# IRIX: bsd.lib.mk links shared libraries with ld -nostdlib; add the compiler
# runtime, which holds the libc add-ons (__irix_*) that the objects call.
.if ${OPSYS} == "IRIX"
MAKE_FLAGS+=	SHLIB_LDENDFILE="$$(${CC} -print-libgcc-file-name)"
.endif

.include "../../mk/bsd.pkg.mk"
