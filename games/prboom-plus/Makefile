# $NetBSD: Makefile,v 1.23 2026/09/02 19:02:21 wiz Exp $

DISTNAME=	prboom-plus-2.6.66
PKGREVISION=	7
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=coelckers/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/coelckers/prboom-plus
COMMENT=	Multiplayer-capable and modified version of DOOM
LICENSE=	gnu-gpl-v2

USE_LANGUAGES=	c99 c++
USE_CMAKE=	yes
USE_TOOLS+=	gmake pkg-config

WRKSRC=		${WRKDIR}/prboom-plus-${PKGVERSION_NOREV}/prboom2

# DOOMWADDIR is intentionally shared with other Doom packages
DOOMWADDIR=	share/doom

CONFIGURE_DIRS=	build
CMAKE_ARG_PATH=	..
CMAKE_CONFIGURE_ARGS+=	-DCMAKE_BUILD_TYPE=Release
CMAKE_CONFIGURE_ARGS+=	-DPRBOOMDATADIR=${PREFIX}/${DOOMWADDIR}
CMAKE_CONFIGURE_ARGS+=	-DDOOMWADDIR=${PREFIX}/${DOOMWADDIR}
CMAKE_CONFIGURE_ARGS+=	-DWITH_DUMB=OFF
CMAKE_CONFIGURE_ARGS+=	-DWITH_FLUIDSYNTH=OFF
CMAKE_CONFIGURE_ARGS+=	-DWITH_PORTMIDI=OFF
CMAKE_CONFIGURE_ARGS+=  -DCMAKE_POLICY_VERSION_MINIMUM=3.5

# Process INSTALL.pkgsrc
SUBST_CLASSES+=		install
SUBST_STAGE.install=	do-configure
SUBST_MESSAGE.install=	Preparing INSTALL.pkgsrc file ...
SUBST_FILES.install=	${WRKDIR}/INSTALL.pkgsrc
SUBST_SED.install=	-e 's,DOOMWADDIR,${PREFIX}/${DOOMWADDIR},'

INSTALLATION_DIRS=	share/applications share/icons/hicolor/scalable/apps

pre-configure:
	cd ${WRKSRC}; mkdir build
	${CP} ${FILESDIR}/INSTALL.pkgsrc ${WRKDIR}

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# A cross build imports rdatawad (it makes prboom-plus.wad, a little-endian
# format) from a native build: build it for the build host, with a config.h
# of its own (the target's says WORDS_BIGENDIAN, all rdatawad takes from it),
# and hand cmake an import file for it.
CMAKE_CONFIGURE_ARGS+=	-DIMPORT_EXECUTABLES=${WRKDIR}/ImportExecutables.cmake
.PHONY: prboom-import-file prboom-host-rdatawad
pre-configure: prboom-import-file
prboom-import-file:
	${PRINTF} 'add_executable(rdatawad IMPORTED)\nset_property(TARGET rdatawad PROPERTY IMPORTED_LOCATION %s)\n' \
		${WRKDIR}/rdatawad > ${WRKDIR}/ImportExecutables.cmake
pre-configure: prboom-host-rdatawad
prboom-host-rdatawad:
	${MKDIR} ${WRKDIR}/rdatawad-inc
	${TOUCH} ${WRKDIR}/rdatawad-inc/config.h
	cd ${WRKSRC}/data && ${NATIVE_CC} -I${WRKDIR}/rdatawad-inc \
		-o ${WRKDIR}/rdatawad rd_main.c rd_util.c rd_output.c \
		rd_sound.c rd_palette.c rd_graphic.c
.endif

post-install:
	${INSTALL_DATA} ${WRKSRC}/ICONS/prboom-plus.desktop \
		${DESTDIR}${PREFIX}/share/applications/prboom-plus.desktop
	${INSTALL_DATA} ${WRKSRC}/ICONS/prboom-plus.svg \
		${DESTDIR}${PREFIX}/share/icons/hicolor/scalable/apps/prboom-plus.svg
	${INSTALL_DATA} ${WRKDIR}/INSTALL.pkgsrc \
		${DESTDIR}${PREFIX}/share/doc/prboom-plus/INSTALL.pkgsrc

.include "../../audio/SDL2_mixer/buildlink3.mk"
.include "../../audio/libmad/buildlink3.mk"
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.include "../../devel/pcre/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/SDL2_image/buildlink3.mk"
.include "../../graphics/glu/buildlink3.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../multimedia/libogg/buildlink3.mk"
.include "../../net/SDL2_net/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"

.include "../../mk/bsd.pkg.mk"
