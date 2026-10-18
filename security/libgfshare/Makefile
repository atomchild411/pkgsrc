# $NetBSD: Makefile,v 1.6 2026/01/04 15:37:43 wiz Exp $

DISTNAME=	libgfshare-1.0.5
CATEGORIES=	security
#MASTER_SITES=	https://www.digital-scurf.org/files/libgfshare/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	agc@NetBSD.org
#HOMEPAGE=	http://www.digital-scurf.org/software/libgfshare
COMMENT=	Library to implement Shamir's secret sharing scheme
LICENSE=	mit

USE_TOOLS+=	gmake
USE_LIBTOOL=	yes
GNU_CONFIGURE=	yes

BUILDLINK_TRANSFORM.Darwin+=	rm:-Wl,-O1
BUILDLINK_TRANSFORM.SunOS+=	rm:-Wl,-O1

.include "../../mk/bsd.fast.prefs.mk"
# The build runs gfshare_maketable to write libgfshare_tables.h (GF(2^8)
# log tables, printed as C): run a copy built for the build host.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		maketable
SUBST_STAGE.maketable=	pre-configure
SUBST_FILES.maketable=	Makefile.in
SUBST_SED.maketable=	-e 's,\./gfshare_maketable$$(EXEEXT) >,./gfshare_maketable_host >,'
pre-build: gfshare-host-maketable
.PHONY: gfshare-host-maketable
gfshare-host-maketable:
	cd ${WRKSRC} && ${NATIVE_CC} -o gfshare_maketable_host src/gfshare_maketable.c
.endif

.include "../../mk/bsd.pkg.mk"
