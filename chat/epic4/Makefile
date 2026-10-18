# $NetBSD: Makefile,v 1.58 2026/07/16 19:01:26 wiz Exp $

DISTNAME=	epic4-2.10.2
PKGREVISION=	15
CATEGORIES=	chat
MASTER_SITES=	https://ftp.epicsol.org/pub/epic/EPIC4-PRODUCTION/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.epicsol.org/
COMMENT=	The (E)nhanced (P)rogrammable (I)RC-II (C)lient

GNU_CONFIGURE=	YES

INSTALL_MAKE_FLAGS+=	IP=${DESTDIR}

CFLAGS.OSF1+=	-D_SOCKADDR_LEN

.include "options.mk"

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# my_test (test(1) with -nt) runs at install time: build it for the build
# machine.
SUBST_CLASSES+=		mytest
SUBST_STAGE.mytest=	pre-configure
SUBST_MESSAGE.mytest=	Building my_test for the build machine.
SUBST_FILES.mytest=	Makefile.in
SUBST_SED.mytest=	-e 's,^	$$(CC) -c @srcdir@/test.c$$,	$$(CC_FOR_BUILD) -c @srcdir@/test.c,'
SUBST_SED.mytest+=	-e 's,^	$$(CC) test.o -o my_test$$,	$$(CC_FOR_BUILD) test.o -o my_test,'
.endif

.include "../../mk/termcap.buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
