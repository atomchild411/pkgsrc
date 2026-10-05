# $NetBSD: Makefile,v 1.1 2025/02/07 16:01:08 pho Exp $

DISTNAME=	libparserutils-0.2.5-src
PKGNAME=	${DISTNAME:S/-src$//}
PKGREVISION=	2
CATEGORIES=	textproc
MASTER_SITES=	https://download.netsurf-browser.org/libs/releases/
WRKSRC=		${WRKDIR}/${PKGNAME_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.netsurf-browser.org/projects/libparserutils/
COMMENT=	Library for building efficient parsers
LICENSE=	mit

USE_LANGUAGES=		c
USE_CC_FEATURES=	c99
USE_TOOLS+=		gmake perl

MAKE_ENV+=	PREFIX=${PREFIX:Q}
MAKE_ENV+=	COMPONENT_TYPE=lib-shared
# The build system is a tool: installed for the build machine (TOOLBASE).
MAKE_ENV+=	NSSHARED=${TOOLBASE}/share/netsurf-buildsystem

BUILDLINK_TRANSFORM+=	rm:-Werror

# The shared library calls iconv: record it where iconv is not in libc.
LDFLAGS+=	${BUILDLINK_LDADD.iconv}

TOOL_DEPENDS+=	netsurf-buildsystem-[0-9]*:../../devel/netsurf-buildsystem

# The static library as well, for programs that must need nothing else at
# run time (www/netscape5's irix-motif option links it in).  It is built
# without the iconv filter (its own UTF-8, UTF-16, ISO 8859 and Windows
# codecs only), so that it needs nothing more either.
post-build:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} COMPONENT_TYPE=lib-static \
	    CFLAGS=${CFLAGS:Q}\ -DWITHOUT_ICONV_FILTER \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} ${BUILD_TARGET}

post-install:
	${INSTALL_DATA} ${WRKSRC}/build-*-lib-static/libparserutils.a ${DESTDIR}${PREFIX}/lib

.include "../../converters/libiconv/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
