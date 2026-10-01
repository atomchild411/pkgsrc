# $NetBSD: Makefile,v 1.33 2023/02/26 06:40:52 wiz Exp $

DISTNAME=	cabextract-1.11
CATEGORIES=	archivers
MASTER_SITES=	https://www.cabextract.org.uk/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.cabextract.org.uk/
COMMENT=	Microsoft cabinet (.CAB) file extractor
LICENSE=	gnu-gpl-v3

USE_TOOLS+=		gmake
GNU_CONFIGURE=		yes
TEST_TARGET=		check

.include "../../mk/bsd.prefs.mk"
# The bundled libmspack is built with MSPACK_NO_DEFAULT_SYSTEM, which
# defines its own memcmp and memset; on IRIX <sys/types.h> brings in
# <string.h>'s, and the two clash. Use the libmspack package instead.
.if ${OPSYS} == "IRIX"
CONFIGURE_ARGS+=	--with-external-libmspack
USE_TOOLS+=		pkg-config
.include "../../archivers/libmspack/buildlink3.mk"
.endif

.include "../../mk/bsd.pkg.mk"
