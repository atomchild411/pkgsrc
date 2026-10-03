# $NetBSD: Makefile,v 1.41 2026/08/24 18:35:28 drixter Exp $

DISTNAME=	gzip-1.14
PKGREVISION=	1
CATEGORIES=	archivers
# does not provide uncompressed tarball, needed due to bootstrapping
#MASTER_SITES=	${MASTER_SITE_GNU:=gzip/}
MASTER_SITES=	${MASTER_SITE_LOCAL}
EXTRACT_SUFX=	.tar

MAINTAINER=	drixter@e-utp.net
HOMEPAGE=	https://www.gnu.org/software/gzip/gzip.html
COMMENT=	Compress or expand files
LICENSE=	gnu-gpl-v3

CONFLICTS+=		gzip-base-[0-9]* gzip-info-[0-9]* zutils-[0-9]*

GNU_CONFIGURE=	yes
# zless is installed only if configure finds less on the build machine;
# the PLIST always has it.
CONFIGURE_ENV+=	ac_cv_prog_LESS=less
MAKE_FLAGS+=	manlinks=so
INFO_FILES=	yes
CHECK_PERMS=	no	# can't depend on checkperms; its distfile is gzipped

.include "../../mk/bsd.pkg.mk"
