# $NetBSD: Makefile,v 1.21 2026/09/02 19:02:09 wiz Exp $

DISTNAME=	1.4.1
PKGNAME=	ecwolf-${DISTNAME}
PKGREVISION=	6
CATEGORIES=	games
MASTER_SITES=	https://bitbucket.org/ecwolf/ecwolf/get/
DIST_SUBDIR=	ecwolf

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://bitbucket.org/ecwolf/ecwolf
COMMENT=	Advanced port of Wolfenstein 3D
LICENSE=	gnu-gpl-v2

WRKSRC=		${WRKDIR}/ecwolf-ecwolf-8cf8d23a6da3

USE_TOOLS+=	pkg-config
USE_LANGUAGES=	c c++

# malloc_usable_size()...
LDFLAGS.NetBSD+=	-ljemalloc

SUBST_CLASSES+=		paths
SUBST_STAGE.paths=	pre-configure
SUBST_FILES.paths+=	docs/ecwolf.6
SUBST_FILES.paths+=	src/wl_iwad.cpp
SUBST_SED.paths=	-e 's,/usr/local/share/games/wolf3d,${PREFIX}/share/ecwolf,g'
SUBST_VARS.paths=	PREFIX

INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	${PKGMANDIR}/man6
INSTALLATION_DIRS+=	libexec
INSTALLATION_DIRS+=	share/ecwolf

INSTALLATION_DIRS+=	share/applications
INSTALLATION_DIRS+=	share/icons/hicolor/96x96/apps
INSTALLATION_DIRS+=	share/icons/hicolor/72x72/apps
INSTALLATION_DIRS+=	share/icons/hicolor/48x48/apps
INSTALLATION_DIRS+=	share/icons/hicolor/36x36/apps

pre-configure:
	${SED} -e 's,@PREFIX@,${PREFIX},g' < ${FILESDIR}/ecwolf.sh.in > \
	    ${WRKSRC}/ecwolf.sh

post-install:
	${MV} ${DESTDIR}${PREFIX}/games/ecwolf \
		${DESTDIR}${PREFIX}/libexec/ecwolf
	${INSTALL_SCRIPT} ${WRKSRC}/ecwolf.sh \
		${DESTDIR}${PREFIX}/bin/ecwolf
	${INSTALL_DATA} ${WRKSRC}/${CMAKE_BUILD_DIR}/ecwolf.pk3 \
		${DESTDIR}${PREFIX}/share/ecwolf/ecwolf.pk3
	${INSTALL_MAN} ${WRKSRC}/docs/ecwolf.6 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man6/ecwolf.6
	${INSTALL_DATA} ${FILESDIR}/ecwolf.desktop \
		${DESTDIR}${PREFIX}/share/applications/ecwolf.desktop
	${INSTALL_DATA} ${WRKSRC}/android-libs/launcher/res/drawable-ldpi/ic_launcher.png \
		${DESTDIR}${PREFIX}/share/icons/hicolor/36x36/apps/ecwolf.png
	${INSTALL_DATA} ${WRKSRC}/android-libs/launcher/res/drawable-mdpi/ic_launcher.png \
		${DESTDIR}${PREFIX}/share/icons/hicolor/48x48/apps/ecwolf.png
	${INSTALL_DATA} ${WRKSRC}/android-libs/launcher/res/drawable-hdpi/ic_launcher.png \
		${DESTDIR}${PREFIX}/share/icons/hicolor/72x72/apps/ecwolf.png
	${INSTALL_DATA} ${WRKSRC}/android-libs/launcher/res/drawable-xhdpi/ic_launcher.png \
		${DESTDIR}${PREFIX}/share/icons/hicolor/96x96/apps/ecwolf.png

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# A cross build imports zipdir (it packs ecwolf.pk3, a zip file) from a
# native build: build it for the build host (the bundled LZMA SDK with it,
# the build machine's zlib and bzip2) and hand cmake an import file for it.
ECWOLF_LZMA_SRCS=	7zArcIn.c 7zBuf.c 7zCrc.c 7zCrcOpt.c 7zDec.c 7zStream.c \
			Bcj2.c Bra.c Bra86.c BraIA64.c CpuArch.c Delta.c LzFind.c \
			Lzma2Dec.c LzmaDec.c LzmaEnc.c Ppmd7.c Ppmd7Dec.c
CMAKE_CONFIGURE_ARGS+=	-DIMPORT_EXECUTABLES=${WRKDIR}/ImportExecutables.cmake
.PHONY: ecwolf-host-zipdir
pre-configure: ecwolf-host-zipdir
ecwolf-host-zipdir:
	${PRINTF} 'add_executable(zipdir IMPORTED)\nset_property(TARGET zipdir PROPERTY IMPORTED_LOCATION %s)\n' \
		${WRKDIR}/zipdir > ${WRKDIR}/ImportExecutables.cmake
	cd ${WRKSRC}/deps/lzma/C && ${NATIVE_CC} -D_7ZIP_PPMD_SUPPPORT -D_7ZIP_ST \
		-I. -I${TOOLBASE}/include -o ${WRKDIR}/zipdir \
		${WRKSRC}/tools/zipdir/zipdir.c ${ECWOLF_LZMA_SRCS} \
		-L${TOOLBASE}/lib -Wl,-rpath,${TOOLBASE}/lib -lz -lbz2

# gdtoa's arith.h and gd_qnan.h come from programs run on the target; a
# cross build has to supply them: big-endian IEEE, and MIPS's (pre-R6)
# quiet NaNs, which have the top mantissa bit clear.
.PHONY: ecwolf-gdtoa-headers
post-configure: ecwolf-gdtoa-headers
ecwolf-gdtoa-headers:
	${PRINTF} '#define IEEE_MC68k\n#define Arith_Kind_ASL 2\n#define Double_Align\n' \
		> ${WRKSRC}/${CMAKE_BUILD_DIR}/deps/gdtoa/arith.h
	${PRINTF} '#define f_QNAN 0x7fbfffff\n#define d_QNAN0 0x7ff7ffff\n#define d_QNAN1 0xffffffff\n' \
		> ${WRKSRC}/${CMAKE_BUILD_DIR}/deps/gdtoa/gd_qnan.h
.endif

.include "../../devel/cmake/build.mk"
.include "../../archivers/bzip2/buildlink3.mk"
.include "../../audio/SDL2_mixer/buildlink3.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../net/SDL2_net/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../x11/gtk3/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
