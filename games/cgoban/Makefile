# $NetBSD: Makefile,v 1.21 2025/11/17 11:00:47 wiz Exp $

DISTNAME=	cgoban-1.9.14
CATEGORIES=	games x11
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=cgoban1/}

MAINTAINER=	bad@NetBSD.org
HOMEPAGE=	https://cgoban1.sourceforge.net/
COMMENT=	The complete goban.  A Go server client and sgf viewer/editor

MAKE_JOBS_SAFE=		no

GNU_CONFIGURE=	yes

# When cross-compiling, configure skips its type size and byte order
# checks (they need a configure.h edited by hand). Run them: autoconf
# answers them at compile time (or from config.site).
.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		cross
SUBST_STAGE.cross=	pre-configure
SUBST_FILES.cross=	configure
SUBST_SED.cross=	-e 's,^if test "$$cross_compiling" = "yes" ; then$$,if false ; then,'
.endif

INSTALLATION_DIRS=	${PKGMANDIR}/man6 share/misc

.include "../../x11/libX11/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
