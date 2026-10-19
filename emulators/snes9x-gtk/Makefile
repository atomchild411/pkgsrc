# $NetBSD: Makefile,v 1.127 2026/09/02 19:01:59 wiz Exp $

PKGREVISION=	16
.include "../../emulators/snes9x/Makefile.common"

PKGNAME=	snes9x-gtk-${SNES9X_VERSION}

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	Super Nintendo Entertainment System (SNES) emulator (GUI version)

USE_TOOLS+=	pkg-config
USE_TOOLS+=	msgfmt xgettext
USE_TOOLS+=	gawk

USE_CXX_FEATURES+=	c++17
FORCE_CXX_STD=		c++17

USE_PKGLOCALEDIR=	yes

CMAKE_CONFIGURE_ARGS+=	-DUSE_SYSTEMZIP=ON
CMAKE_CONFIGURE_ARGS+=	-DUSE_SLANG=OFF
CMAKE_CONFIGURE_ARGS+=	-DENABLE_PCH=OFF
CMAKE_CONFIGURE_ARGS+=	-DCMAKE_INSTALL_LOCALEDIR=${PKGLOCALEDIR}/locale

TOOL_DEPENDS+=	gettext-m4-[0-9]*:../../devel/gettext-m4

CONFIGURE_DIR=	gtk

USE_CXX_FEATURES+=	c++17 filesystem

.include "../../mk/oss.buildlink3.mk"

.if ${OSS_TYPE} != "none"
SUBST_CLASSES+=		oss
SUBST_STAGE.oss=	pre-configure
SUBST_MESSAGE.oss=	Correct path to OSS device.
SUBST_FILES.oss+=	common/audio/s9x_sound_driver_oss.cpp
SUBST_SED.oss=		-e "s,/dev/dsp,${DEVOSSAUDIO},g"
LDFLAGS+=		${LIBOSSAUDIO}
.else
CMAKE_CONFIGURE_ARGS+=		-DUSE_OSS=OFF
.endif

LDFLAGS.SunOS+=		-lsocket -lnsl

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# sourcify turns the UI file and icon into C++ during the build: build it
# for the build host.
SUBST_CLASSES+=		sourcify
SUBST_STAGE.sourcify=	pre-configure
SUBST_FILES.sourcify=	gtk/CMakeLists.txt
SUBST_SED.sourcify=	-e 's,COMMAND sourcify ,COMMAND ${WRKDIR}/sourcify ,'
SUBST_SED.sourcify+=	-e 's,DEPENDS sourcify),),'
SUBST_MESSAGE.sourcify=	Using a sourcify built for the build host.

pre-configure:
	${NATIVE_CC} -o ${WRKDIR}/sourcify ${WRKSRC}/gtk/src/sourcify.c
.endif

.include "options.mk"
.include "../../devel/cmake/build.mk"
.include "../../archivers/minizip/buildlink3.mk"
.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../graphics/libepoxy/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../x11/gtkmm3/buildlink3.mk"
.include "../../x11/libXrandr/buildlink3.mk"
.include "../../x11/libXv/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../mk/dlopen.buildlink3.mk"
BUILDLINK_TRANSFORM+=	opt:-ldl:${BUILDLINK_LDADD.dl:Q}
.include "../../mk/atomic64.mk"
.include "../../mk/bsd.pkg.mk"
