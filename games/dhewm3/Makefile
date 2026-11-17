# $NetBSD: Makefile,v 1.44 2026/09/02 19:02:08 wiz Exp $

DISTNAME=	dhewm3-1.5.4
PKGREVISION=	16
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=dhewm/}
GITHUB_PROJECT=	dhewm3
GITHUB_RELEASE=	${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://dhewm3.org/
COMMENT=	Source port of the original Doom 3
LICENSE=	gnu-gpl-v3

WRKSRC=		${WRKDIR}/${PKGNAME_NOREV}
USE_TOOLS+=	pkg-config
USE_LANGUAGES=	c gnu++11

USE_CXX_FEATURES+=	c++11

CONFIGURE_DIR=	neo

CMAKE_CONFIGURE_ARGS+=	-Wno-dev
CMAKE_CONFIGURE_ARGS+=	-DDEDICATED=ON

# The project adds -DNDEBUG only in CMAKE_CXX_FLAGS_RELEASE, which pkgsrc's
# CMAKE_PKGSRC_BUILD_FLAGS leaves out: without it, debug assertions abort
# the game in normal play (CollisionModel_rotate.cpp, a crane in
# mc_underground).
CXXFLAGS+=	-DNDEBUG

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "NetBSD"
CFLAGS+=	-DIOAPI_NO_64
CXXFLAGS+=	-DIOAPI_NO_64
.endif

INSTALLATION_DIRS+=	share/applications
INSTALLATION_DIRS+=	share/pixmaps
INSTALLATION_DIRS+=	share/dhewm3/base

post-extract:
	${CP} ${FILESDIR}/Simd_Revenir.cpp ${FILESDIR}/Simd_Revenir.h \
	    ${WRKSRC}/neo/idlib/math/

# The controller bindings are installed for "exec gamepad.cfg" (MESSAGE).
post-install:
	${INSTALL_DATA} ${WRKSRC}/neo/sys/linux/setup/image/doom3.png \
	    ${DESTDIR}${PREFIX}/share/pixmaps
	${INSTALL_DATA} ${FILESDIR}/dhewm3.desktop \
	    ${DESTDIR}${PREFIX}/share/applications
	${INSTALL_DATA} ${WRKSRC}/base/gamepad.cfg ${WRKSRC}/base/gamepad-d3xp.cfg \
	    ${DESTDIR}${PREFIX}/share/dhewm3/base

.include "../../devel/cmake/build.mk"
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../audio/openal-soft/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
