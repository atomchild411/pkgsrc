# $NetBSD: Makefile,v 1.1 2026/02/15 16:46:07 manu Exp $

MODNAME=		pspell
PECL_VERSION=		1.0.1
CATEGORIES+=		textproc

MAINTAINER=		pkgsrc-users@NetBSD.org
COMMENT=		PHP extension for pspell support, for PHP >= 8.4
#PKGREVISION=		1
LICENSE=		php

PHP_VERSIONS_ACCEPTED=	84

USE_TOOLS+=		pkg-config

CONFIGURE_ARGS+=	--with-${MODNAME}=shared,${BUILDLINK_PREFIX.aspell}

.include "../../lang/php/ext.mk"
.include "../../textproc/aspell/buildlink3.mk"
.if ${OPSYS} == "IRIX"
# aspell gets snprintf from libnbcompat there (USE_FEATURES), and its
# libtool archives, which this links through, name -lnbcompat.
.include "../../pkgtools/libnbcompat/buildlink3.mk"
.endif
.include "../../mk/bsd.pkg.mk"
