# $NetBSD: Makefile,v 1.54 2026/07/13 04:35:28 wiz Exp $

DISTNAME=	allegro-4.4.3.1
PKGREVISION=	9
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=liballeg/}
GITHUB_PROJECT=	allegro5
GITHUB_RELEASE=	${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://liballeg.org/
COMMENT=	Cross-platform library aimed at video game programming (4.x branch)
#LICENSE=	# TODO: (see mk/license.mk)

USE_CMAKE=	yes
USE_TOOLS+=	pkg-config makeinfo
USE_LANGUAGES=	c c++

INFO_FILES=	yes
CMAKE_CONFIGURE_ARGS+=	-DINFODIR=${PKGINFODIR:Q}
CMAKE_CONFIGURE_ARGS+=	-DCMAKE_POLICY_VERSION_MINIMUM=3.5

.include "../../mk/bsd.fast.prefs.mk"
# CMakeLists.txt runs a constructor-attribute test (check_c_source_runs),
# which a cross build cannot; IRIX's runtime runs constructors.
.if ${USE_CROSS_COMPILE:U:tl} == "yes" && ${OPSYS} == "IRIX"
CMAKE_CONFIGURE_ARGS+=	-DALLEGRO_USE_CONSTRUCTOR_EXITCODE=0
.endif
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# docs/CMakeLists.txt skips the documentation when cross-compiling: it runs
# makedoc, which it builds. Build makedoc (plain C) for the build host and
# use it as an imported executable.
SUBST_CLASSES+=		makedoc
SUBST_STAGE.makedoc=	pre-configure
SUBST_FILES.makedoc=	docs/CMakeLists.txt
SUBST_SED.makedoc=	-e 's,^if(NOT WANT_DOCS OR CMAKE_CROSSCOMPILING)$$,if(NOT WANT_DOCS),'
SUBST_SED.makedoc+=	-e 's,^add_executable(makedoc$$,add_executable(makedoc IMPORTED)\nset_property(TARGET makedoc PROPERTY IMPORTED_LOCATION ${WRKDIR}/makedoc)\nadd_executable(makedoc-target,'

pre-configure: allegro-host-makedoc
.PHONY: allegro-host-makedoc
allegro-host-makedoc:
	cd ${WRKSRC}/docs/src/makedoc && ${NATIVE_CC} -O -o ${WRKDIR}/makedoc *.c
.endif
.if ${OPSYS} == "IRIX"
# No librt: clock_gettime is in libc. (A file: the build also lists
# RT_LIBRARY as a dependency.)
CMAKE_CONFIGURE_ARGS+=	-DRT_LIBRARY=${_CROSS_DESTDIR}/usr/lib${LIBABISUFFIX}/libc.so
.endif

PLIST_SUBST+=	ALLEG_VER=${PKGVERSION_NOREV:R}

.include "../../mk/oss.buildlink3.mk"

.if ${OSS_TYPE} != "none"
SUBST_CLASSES+=		oss
SUBST_STAGE.oss=	pre-configure
SUBST_MESSAGE.oss=	Correcting the path to the OSS device.
SUBST_FILES.oss+=	src/unix/uoss.c
SUBST_SED.oss+=		-e "s,/dev/dsp,${DEVOSSAUDIO},g"
.endif

SUBST_CLASSES.NetBSD+=	ossmidi
SUBST_CLASSES.SunOS+=	ossmidi
SUBST_STAGE.ossmidi=	pre-configure
SUBST_MESSAGE.ossmidi=	OS does not have full OSS MIDI support.
SUBST_FILES.ossmidi=	CMakeLists.txt
SUBST_SED.ossmidi=	-e 's/ALLEGRO_WITH_OSSMIDI 1/ALLEGRO_WITH_OSSMIDI 0/'

PKGCONFIG_OVERRIDE+=	misc/logg.pc.in
PKGCONFIG_OVERRIDE+=	misc/loadpng.pc.in
PKGCONFIG_OVERRIDE+=	misc/allegrogl.pc.in
PKGCONFIG_OVERRIDE+=	misc/jpgalleg.pc.in
PKGCONFIG_OVERRIDE+=	misc/allegro.pc.in

INSTALLATION_DIRS=	share/aclocal

post-install:
	${INSTALL_DATA} ${WRKSRC}/misc/allegro.m4 ${DESTDIR}${PREFIX}/share/aclocal

.include "options.mk"

# IRIX: the SGI audio library (AL) digital sound driver.
.if ${OPSYS} == "IRIX"
PLIST_SRC+=	PLIST.IRIX
.endif
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/glu/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../multimedia/libogg/buildlink3.mk"
.include "../../x11/libICE/buildlink3.mk"
.include "../../x11/libSM/buildlink3.mk"
.include "../../x11/libX11/buildlink3.mk"
.include "../../x11/libXcursor/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libXpm/buildlink3.mk"
.include "../../x11/libXxf86dga/buildlink3.mk"
.include "../../x11/libXxf86vm/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
