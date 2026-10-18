# $NetBSD: Makefile,v 1.18 2026/05/15 19:04:22 ktnb Exp $
#

DISTNAME=	mairix-0.24
CATEGORIES=	mail
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=mairix/}

MAINTAINER=	simonb@NetBSD.org
HOMEPAGE=	http://www.rc0.org.uk/mairix/
COMMENT=	Program for indexing and searching email messages
LICENSE=	gnu-gpl-v2

HAS_CONFIGURE=		yes
CONFIGURE_ARGS+=	--prefix=${PREFIX}
CONFIGURE_ARGS+=	--mandir=${PREFIX}/${PKGMANDIR}

USE_TOOLS+=		bison flex

.include "../../mk/bsd.fast.prefs.mk"
# The build runs dfasyn (a scanner generator) from its dfasyn/ subdirectory.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		dfasyn
SUBST_STAGE.dfasyn=	pre-configure
SUBST_FILES.dfasyn=	Makefile.in
SUBST_SED.dfasyn=	-e 's,cd dfasyn ; $$(MAKE) CC="$$(CC)" CFLAGS="$$(CFLAGS)",cd dfasyn ; $$(MAKE) CC="${NATIVE_CC}" CFLAGS="",'
.endif

.include "../../mk/bsd.pkg.mk"
