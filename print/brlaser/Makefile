# $NetBSD: Makefile,v 1.29 2026/09/02 19:04:07 wiz Exp $

DISTNAME=		brlaser-6.2.8
PKGREVISION=		5
CATEGORIES=		print
MASTER_SITES=		${MASTER_SITE_GITHUB:=Owl-Maintain/}
GITHUB_TAG=		refs/tags/v${PKGVERSION_NOREV}

MAINTAINER=		schmonz@NetBSD.org
HOMEPAGE=		https://github.com/Owl-Maintain/brlaser/
COMMENT=		CUPS driver for Brother laser printers
LICENSE=		gnu-gpl-v2

WRKSRC=			${WRKDIR}/${DISTNAME}

USE_LANGUAGES=		c++
USE_CXX_FEATURES+=	c++11

.include "../../mk/bsd.prefs.mk"

.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# cups-config is the build host's: it answers with the tools prefix.
CMAKE_CONFIGURE_ARGS+=	-DCUPS_DATA_DIR=${PREFIX}/share/cups
CMAKE_CONFIGURE_ARGS+=	-DCUPS_SERVER_BIN=${PREFIX}/libexec/cups
.endif

.include "../../devel/cmake/build.mk"
.include "../../print/libcups/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
