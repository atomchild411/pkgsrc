# $NetBSD: Makefile,v 1.1 2025/02/07 16:02:09 pho Exp $

DISTNAME=	libcss-0.9.2-src
PKGNAME=	${DISTNAME:S/-src$//}
PKGREVISION=	7
CATEGORIES=	textproc
MASTER_SITES=	https://download.netsurf-browser.org/libs/releases/
WRKSRC=		${WRKDIR}/${PKGNAME_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.netsurf-browser.org/projects/libcss/
COMMENT=	CSS parser and selection engine
LICENSE=	mit

USE_LANGUAGES=		c
USE_CC_FEATURES=	c99
USE_TOOLS+=		gmake perl pkg-config

MAKE_ENV+=	PREFIX=${PREFIX:Q}
MAKE_ENV+=	COMPONENT_TYPE=lib-shared
# The build type (the build system's VARIANT): a VARIANT in the environment
# (an IRIX ABI variant, say) would make a debug build (-O0, tracing).
MAKE_ENV+=	VARIANT=release
# The build system is a tool: installed for the build machine (TOOLBASE).
MAKE_ENV+=	NSSHARED=${TOOLBASE}/share/netsurf-buildsystem
MAKE_ENV+=	PKGCONFIG=${TOOLS_CMD.pkg-config:Q}

BUILDLINK_TRANSFORM+=	rm:-Werror

TOOL_DEPENDS+=	netsurf-buildsystem-[0-9]*:../../devel/netsurf-buildsystem

# The static library as well, for programs that must need nothing else at
# run time (www/netscape5's irix-motif option links it in).
post-build:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} COMPONENT_TYPE=lib-static \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} ${BUILD_TARGET}

post-install:
	${INSTALL_DATA} ${WRKSRC}/build-*-lib-static/libcss.a ${DESTDIR}${PREFIX}/lib

.include "../../mk/bsd.prefs.mk"

.if ${USE_CROSS_COMPILE:tl} == "yes"
# gen_parser writes the property parsers during the build: compile it for
# the build machine.  BUILD and HOST are named so the build system still
# takes its native path (it would compare BUILD_CC's machine with CC's).
MAKE_ENV+=	BUILD_CC=${NATIVE_CC:Q}
MAKE_ENV+=	BUILD=${MACHINE_GNU_PLATFORM} HOST=${MACHINE_GNU_PLATFORM}
.endif

.include "../../devel/libwapcaplet/buildlink3.mk"
.include "../../textproc/libparserutils/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
