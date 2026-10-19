# $NetBSD: Makefile,v 1.14 2026/05/14 16:40:39 ryoon Exp $

DISTNAME=	gcli-2.2.0
PKGREVISION=	11
CATEGORIES=	devel
MASTER_SITES=	https://herrhotzenplotz.de/gcli/releases/gcli-2.2.0/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	tm@NetBSD.org
HOMEPAGE=	https://herrhotzenplotz.de/gcli/
COMMENT=	Portable CLI tool for interacting with GitHub/Lab/Tea
LICENSE=	2-clause-bsd

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes
USE_TOOLS+=	pkg-config

PKGCONFIG_OVERRIDE+=	libgcli.pc.in

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# pgen, run at build time to write the JSON parsers (C source), is for the
# build host.
SUBST_CLASSES+=		pgen
SUBST_STAGE.pgen=	pre-configure
SUBST_FILES.pgen=	Makefile.in
SUBST_SED.pgen=		-e 's|^	\$$(AM_V_CCLD)\$$(LINK) \$$(pgen_OBJECTS) .*|	${NATIVE_CC} -I. -I$$(srcdir)/include -Isrc/pgen -o $$@ $$(srcdir)/src/pgen/dump_c.c $$(srcdir)/src/pgen/dump_h.c $$(srcdir)/src/pgen/dump_plain.c src/pgen/parser.c src/pgen/lexer.c|'
.endif

.include "../../www/curl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
