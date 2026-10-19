# $NetBSD: Makefile,v 1.18 2026/02/16 08:24:49 wiz Exp $

DISTNAME=		wbd-1.0ucl4
PKGNAME=		wbd-1.0p4
PKGREVISION=		11
CATEGORIES=		mbone tk
MASTER_SITES=		#

MAINTAINER=		pkgsrc-users@NetBSD.org
#HOMEPAGE=		http://www-mice.cs.ucl.ac.uk/multimedia/software/wbd/
COMMENT=		Multicast WhiteBoarD

MAKE_FILE=		makefile
WRKSRC=			${WRKDIR}/wbd
BUILD_TARGET=		wbd
NO_CONFIGURE=		yes

INSTALLATION_DIRS=	bin

.include "../../mk/bsd.prefs.mk"
CFLAGS+=	-DUSE_INTERP_RESULT
MAKE_FLAGS+=	CFLAGS=${CFLAGS:Q}

LDFLAGS.SunOS+=		-lsocket -lnsl

.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# tcl2c turns the Tcl/Tk library scripts into C: build it for the build
# host, and read the target's scripts.
SUBST_CLASSES+=		tcl2c
SUBST_STAGE.tcl2c=	pre-build
SUBST_FILES.tcl2c=	makefile
SUBST_SED.tcl2c=	-e 's,^tcl2c	:	tcl2c\.o,tcl2c	:	tcl2c.c,'
SUBST_SED.tcl2c+=	-e 's,^	$$(CC) $$(CFLAGS) tcl2c\.o $$(LIBS) -o tcl2c,	${NATIVE_CC} -std=gnu89 -o tcl2c tcl2c.c,'
SUBST_MESSAGE.tcl2c=	Building tcl2c for the build host.
MAKE_FLAGS+=		LIBRARY_TCL=${_CROSS_DESTDIR}${PREFIX}/lib/tcl8.6
MAKE_FLAGS+=		LIBRARY_TK=${_CROSS_DESTDIR}${PREFIX}/lib/tk8.6
.endif

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/wbd ${DESTDIR}${PREFIX}/bin/wbd

.include "../../x11/tk/buildlink3.mk"
.include "../../mk/bsd.fast.prefs.mk"
.if ${OPSYS} == "IRIX"
# IRIX has no lex library: flex's libfl has the same yywrap and main.
BUILDLINK_TRANSFORM+=	l:l:fl
.  include "../../devel/flex/buildlink3.mk"
.endif

.include "../../mk/bsd.pkg.mk"
