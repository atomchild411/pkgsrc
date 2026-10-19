# $NetBSD: Makefile,v 1.23 2021/08/27 03:41:41 ryoon Exp $
#

DISTNAME=		xcopilot-0.6.6
PKGREVISION=		2
CATEGORIES=		emulators
#MASTER_SITES=		http://xcopilot.cuspy.com/build/

MAINTAINER=		nathanw@NetBSD.org
#HOMEPAGE=		http://xcopilot.cuspy.com/
COMMENT=		PalmPilot emulator for X
LICENSE=		gnu-gpl-v2

MAKE_JOBS_SAFE=		no

GNU_CONFIGURE=		YES

post-extract:
	${RM} -f ${WRKSRC}/mc68k/custom.c

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# fab_custom, run at build time to write custom.c, is for the build host.
SUBST_CLASSES+=		fabcust
SUBST_STAGE.fabcust=	pre-configure
SUBST_FILES.fabcust=	mc68k/Makefile.in
SUBST_SED.fabcust=	-e 's|^	\$$(CC) -o fab_custom \$$?|	${NATIVE_CC} -I. -I.. -o fab_custom fab_custom.c|'
.endif

.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libXpm/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
