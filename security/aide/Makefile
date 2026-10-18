# $NetBSD: Makefile,v 1.42 2025/11/17 11:01:21 wiz Exp $

DISTNAME=	aide-0.15.1
PKGREVISION=	2
CATEGORIES=	security
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=aide/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://aide.sourceforge.net/
COMMENT=	Free intrusion detection system for checking file integrity
LICENSE=	artistic

GNU_CONFIGURE=	yes
USE_TOOLS+=	bison flex gmake

CHECK_PORTABILITY_SKIP=	contrib/gpg2_update.sh # not needed

.include "../../mk/bsd.prefs.mk"

.if (${OPSYS} == "SunOS" && empty(OS_VERSION:M5.[6-9])) || ${OPSYS} == "IRIX"
# Since Solaris 10, static linking no longer possible; nor on IRIX
CONFIGURE_ARGS+=	--disable-static
.endif

# configure runs a program to choose ino64_t; on IRIX (n32 too) ino_t is 64 bits.
CONFIGURE_ENV.IRIX+=	AIDE_INO_TYPE=ino_t

.include "../../devel/zlib/buildlink3.mk"
.include "../../security/mhash/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
