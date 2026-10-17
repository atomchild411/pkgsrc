# $NetBSD: Makefile,v 1.9 2026/09/02 19:01:54 wiz Exp $

DISTNAME=	FBNeo-1.0.0.2
PKGNAME=	${DISTNAME:tl}
PKGREVISION=	6
CATEGORIES=	emulators
MASTER_SITES=	${MASTER_SITE_GITHUB:=finalburnneo/}
GITHUB_PROJECT=	fbneo
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	nia@NetBSD.org
HOMEPAGE=	https://github.com/finalburnneo/FBNeo
COMMENT=	FinalBurn Neo - the arcade game emulator (SDL2 version)
LICENSE=	fbalpha-license

USE_TOOLS+=	gmake perl
MAKE_FILE=	makefile

WRKSRC=		${WRKDIR}/${DISTNAME}

FORCE_CXX_STD+=	gnu++98
# clang predefines "mips" (as MIPSpro does) in GNU modes, and the MIPS III
# core is "namespace mips".
CFLAGS.IRIX+=	-Umips
CXXFLAGS.IRIX+=	-Umips

BUILD_TARGET=	sdl2

MAKE_FLAGS+=	RELEASEBUILD=1
MAKE_FLAGS+=	FORCE_SYSTEM_LIBPNG=1
MAKE_FLAGS+=	INCLUDE_7Z_SUPPORT=1
MAKE_FLAGS+=	PERL=1

REPLACE_PERL+=	src/dep/scripts/*.pl

.include "../../mk/bsd.prefs.mk"

# The perl scripts only run while building: cross-compiling, the build
# host's perl (TOOLBASE), not IRIX's.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
REPLACE_PERL=		# none
SUBST_CLASSES+=		hostperl
SUBST_STAGE.hostperl=	pre-configure
SUBST_MESSAGE.hostperl=	The build host's perl for the build-time scripts.
SUBST_FILES.hostperl=	src/dep/scripts/*.pl
SUBST_SED.hostperl=	-e '1s|^\#!/usr/bin/perl|\#!${TOOLBASE}/bin/perl|'
# And its generator programs (m68kmake, ctv_make, pgm_sprite_create).
MAKE_FLAGS+=		HOSTCC=${NATIVE_CC:Q} HOSTCFLAGS=-O2
MAKE_FLAGS+=		HOSTCXX=${NATIVE_CXX:Q} HOSTCXXFLAGS=-O2
.endif

.if ${MACHINE_ARCH} == "i386" || ${MACHINE_ARCH} == "x86_64"
TOOL_DEPENDS+=	nasm-[0-9]*:../../devel/nasm
.endif

.include "../../mk/endian.mk"
.if ${MACHINE_ENDIAN} == "little"
MAKE_FLAGS+=	LSB_FIRST=1
.endif

LDFLAGS+=	-lpng -lz

MAKE_JOBS_SAFE=	no

INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	share/applications
INSTALLATION_DIRS+=	share/pixmaps

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/fbneo ${DESTDIR}${PREFIX}/bin
	${INSTALL_DATA} ${FILESDIR}/fbneo.desktop ${DESTDIR}${PREFIX}/share/applications
	${INSTALL_DATA} ${WRKSRC}/projectfiles/xcode/Emulator/Assets.xcassets/AppIcon.appiconset/icon_128.png \
		${DESTDIR}${PREFIX}/share/pixmaps/fbneo.png

.include "../../devel/SDL2/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/SDL2_image/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../mk/bsd.pkg.mk"
