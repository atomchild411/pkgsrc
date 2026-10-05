# $NetBSD: Makefile,v 1.1 2025/02/07 15:59:47 pho Exp $

DISTNAME=	libwapcaplet-0.4.3-src
PKGNAME=	${DISTNAME:S/-src$//}
PKGREVISION=	2
CATEGORIES=	devel
MASTER_SITES=	https://download.netsurf-browser.org/libs/releases/
WRKSRC=		${WRKDIR}/${PKGNAME_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.netsurf-browser.org/projects/libwapcaplet/
COMMENT=	String internment library
LICENSE=	mit

USE_LANGUAGES=		c
USE_CC_FEATURES=	c99
USE_TOOLS+=		gmake

MAKE_ENV+=	PREFIX=${PREFIX:Q}
MAKE_ENV+=	COMPONENT_TYPE=lib-shared
# The build type (the build system's VARIANT): a VARIANT in the environment
# (an IRIX ABI variant, say) would make a debug build (-O0, tracing).
MAKE_ENV+=	VARIANT=release
# The build system is a tool: installed for the build machine (TOOLBASE).
MAKE_ENV+=	NSSHARED=${TOOLBASE}/share/netsurf-buildsystem

BUILDLINK_TRANSFORM+=	rm:-Werror

TOOL_DEPENDS+=	netsurf-buildsystem-[0-9]*:../../devel/netsurf-buildsystem

# The static library as well, for programs that must need nothing else at
# run time (www/netscape5's irix-motif option links it in).
post-build:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} COMPONENT_TYPE=lib-static \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} ${BUILD_TARGET}

post-install:
	${INSTALL_DATA} ${WRKSRC}/build-*-lib-static/libwapcaplet.a ${DESTDIR}${PREFIX}/lib

.include "../../mk/bsd.pkg.mk"
