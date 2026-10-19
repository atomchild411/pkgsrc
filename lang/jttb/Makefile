# $NetBSD: Makefile,v 1.5 2025/08/19 13:44:53 wiz Exp $

DISTNAME=	JTTB-0.6
CATEGORIES=	lang
MASTER_SITES=	${MASTER_SITE_GITHUB:=thorpej/}
GITHUB_PROJECT=	JTTB
GITHUB_TAG=	${PKGVERSION_NOREV}

MAINTAINER=	thorpej@NetBSD.org
HOMEPAGE=	https://github.com/thorpej/JTTB
COMMENT=	Small, portable BASIC interpreter written in C
LICENSE=	2-clause-bsd

USE_LANGUAGES=	c c++

CFLAGS+=	-Wno-error=unknown-pragmas

# build failure, doesn't find tbasm program during build
CMAKE_GENERATORS_INCOMPATIBLE=	ninja
MAKE_JOBS_SAFE=	no

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# tbasm assembles the VM program into a header during the build: build it
# for the build host instead of as an ExternalProject.
CMAKE_CONFIGURE_ARGS+=	-DTbasm_FOUND=1 -DTbasm_EXECUTABLE=${WRKDIR}/tbasm-host

pre-configure:
	${NATIVE_CC} -o ${WRKDIR}/tbasm-host ${WRKSRC}/tbasm/tbasm.c
.endif

.include "../../devel/cmake/build.mk"
.include "../../mk/bsd.pkg.mk"
