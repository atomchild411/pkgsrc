# $NetBSD: Makefile,v 1.1 2025/04/28 13:25:29 wiz Exp $

DISTNAME=	epic5-3.0.3
CATEGORIES=	chat
MASTER_SITES=	https://ftp.epicsol.org/pub/epic/EPIC5-PRODUCTION/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://ftp.epicsol.org/pub/epic/EPIC5-PRODUCTION/
COMMENT=	The (E)nhanced (P)rogrammable (I)RC-II (C)lient
LICENSE=	modified-bsd

GNU_CONFIGURE=	yes

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# stringify runs at build time: build it for the build machine.
SUBST_CLASSES+=		stringify
SUBST_STAGE.stringify=	pre-configure
SUBST_MESSAGE.stringify=	Building stringify for the build machine.
SUBST_FILES.stringify=	source/Makefile.in
SUBST_SED.stringify=	-e '/^stringify: stringify.c$$/{n;s/$$(CC) $$(CFLAGS)/$$(CC_FOR_BUILD)/;}'
.endif

USE_TOOLS+=	perl

.include "../../mk/curses.buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
