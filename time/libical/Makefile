# $NetBSD: Makefile,v 1.64 2026/09/02 19:04:49 wiz Exp $

DISTNAME=	libical-3.0.20
PKGREVISION=	5
CATEGORIES=	time
MASTER_SITES=	${MASTER_SITE_GITHUB:=libical/}
GITHUB_RELEASE=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/libical/libical
COMMENT=	Reference implementation of the iCalendar data type and format (v3)
LICENSE=	gnu-lgpl-v2.1 OR mpl-2.0

CONFLICTS=	libical4-[0-9]*

USE_TOOLS+=	perl pkg-config

CMAKE_CONFIGURE_ARGS+=	-DUSE_BUILTIN_TZDATA=OFF
CMAKE_CONFIGURE_ARGS+=	-DICAL_BUILD_DOCS=OFF
CMAKE_CONFIGURE_ARGS+=	-DCMAKE_DISABLE_FIND_PACKAGE_BerkeleyDB=ON

PKGCONFIG_OVERRIDE+=	libical.pc.in
PKGCONFIG_OVERRIDE+=	src/libical-glib/libical-glib.pc.in

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "NetBSD"
# zone.tab file in /usr/share/zoneinfo
DEPENDS+=	zonetab-[0-9]*:../../time/zonetab
.endif

.if ${USE_CROSS_COMPILE:tl} == "yes"
# libical-glib writes its sources with ical-glib-src-generator, which a
# cross build imports from a native build: build it here for the build
# machine, against its glib2 and libxml2, and give CMake that.
TOOL_DEPENDS+=		glib2-[0-9]*:../../devel/glib2
TOOL_DEPENDS+=		libxml2-[0-9]*:../../textproc/libxml2
_ICAL_GEN_DIR=		${WRKDIR}/native-generator
CMAKE_CONFIGURE_ARGS+=	-DIMPORT_ICAL_GLIB_SRC_GENERATOR=${_ICAL_GEN_DIR}/import.cmake
pre-configure: libical-native-generator
.PHONY: libical-native-generator
libical-native-generator:
	${RUN} ${MKDIR} ${_ICAL_GEN_DIR}
	${RUN} cd ${WRKSRC}/src/libical-glib/tools &&				\
	${NATIVE_CC} -O2 -DG_LOG_DOMAIN='"src-generator"' generator.c xml-parser.c \
	    `PKG_CONFIG_LIBDIR=${TOOLBASE}/lib/pkgconfig ${TOOLBASE}/bin/pkg-config --cflags --libs glib-2.0 libxml-2.0` \
	    -Wl,-rpath,${TOOLBASE}/lib -o ${_ICAL_GEN_DIR}/ical-glib-src-generator
	${RUN} { ${ECHO} 'add_executable(native-ical-glib-src-generator IMPORTED)'; \
	    ${ECHO} 'set_property(TARGET native-ical-glib-src-generator PROPERTY IMPORTED_LOCATION ${_ICAL_GEN_DIR}/ical-glib-src-generator)'; \
	} > ${_ICAL_GEN_DIR}/import.cmake
.endif

# C++ is only needed for test
USE_LANGUAGES=	c c++
TEST_ENV+=	LD_LIBRARY_PATH=${WRKSRC}/${CMAKE_BUILD_DIR}/lib
TEST_TARGET=	test

.include "../../devel/cmake/build.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../textproc/icu/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
