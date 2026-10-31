# $NetBSD: Makefile,v 1.83 2026/09/02 19:00:54 wiz Exp $

DISTNAME=	libmikmod-3.3.13
PKGREVISION=	4
CATEGORIES=	audio
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=mikmod/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://mikmod.sourceforge.net/
COMMENT=	MikMod Sound Library
LICENSE=	gnu-lgpl-v2

USE_CC_FEATURES=	c99
USE_LANGUAGES=		c
USE_LIBTOOL=		yes
USE_TOOLS+=		gmake
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--disable-threads
# The IRIX driver (drv_sgi) calls the IRIX Audio Library, but the library
# was not linked with it: ALseterrorhandler and friends were unresolved.
LIBS.IRIX+=		-laudio
INFO_FILES=		yes
PKGCONFIG_OVERRIDE=	libmikmod.pc.in

.include "options.mk"

.include "../../mk/bsd.pkg.mk"
