# $NetBSD: Makefile,v 1.15 2025/10/01 19:33:29 wiz Exp $

DISTNAME=		xrmap-2.29
PKGNAME=		xrmap-base-2.29
PKGREVISION=		3
CATEGORIES=		geography
#MASTER_SITES=		ftp://ftp.ac-grenoble.fr/ge/geosciences/xrmap/
EXTRACT_SUFX=		.tar.bz2

MAINTAINER=		pkgsrc-users@NetBSD.org
#HOMEPAGE=		http://frmas.free.fr/li_1.htm
COMMENT=		Earth map viewer - base program

MAKE_JOBS_SAFE=		no

USE_IMAKE=		yes
MAKE_FLAGS+=		MANPATH=${PREFIX}/${PKGMANDIR}

INSTALLATION_DIRS+=	share/rmap/factbook

# ctype(3) problems
BROKEN_ON_PLATFORM+=	NetBSD-1[1-9].*-*

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# tools/preproc runs at build time (it writes numdefs.h): build it for
# the build host.
SUBST_CLASSES+=		preproc
SUBST_STAGE.preproc=	pre-configure
SUBST_MESSAGE.preproc=	Building preproc for the build host.
SUBST_FILES.preproc=	tools/Makefile
SUBST_SED.preproc=	-e "s,^	cc preproc.c,	${NATIVE_CC} -Wno-error=implicit-function-declaration preproc.c,"
.endif

.include "../../devel/zlib/buildlink3.mk"
.include "../../x11/libX11/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libXpm/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
