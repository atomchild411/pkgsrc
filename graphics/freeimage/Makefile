# $NetBSD: Makefile,v 1.35 2026/08/03 18:10:25 wiz Exp $

.include "Makefile.common"

PKGNAME=	freeimage-3.18.0
PKGREVISION=	23

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	Library for supporting PNG, BMP, JPEG, and TIFF

# IRIX: left out: FreeImage is dead upstream (last release 2018) with 45 open CVEs.
# Everything that needs it follows.
NOT_FOR_PLATFORM+=	IRIX-*-*

MAKE_FILE=	Makefile.gnu

.include "../../mk/bsd.pkg.mk"
