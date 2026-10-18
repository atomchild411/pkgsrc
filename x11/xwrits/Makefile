# $NetBSD: Makefile,v 1.23 2025/09/21 21:22:40 wiz Exp $

DISTNAME=	xwrits-2.24
CATEGORIES=	x11
MASTER_SITES=	http://www.lcdf.org/~eddietwo/xwrits/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.lcdf.org/~eddietwo/xwrits/
COMMENT=	Wrist break reminder for prevention of repetitive stress injuries

GNU_CONFIGURE=	YES

.include "../../mk/bsd.fast.prefs.mk"
# The build runs giftoc to turn the GIF pictures into C: run a copy built
# for the build host.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		giftoc
SUBST_STAGE.giftoc=	pre-configure
SUBST_FILES.giftoc=	Makefile.in
SUBST_SED.giftoc=	-e 's,^\t\./giftoc -makename,\t./giftoc_host -makename,'
pre-build: xwrits-host-giftoc
.PHONY: xwrits-host-giftoc
xwrits-host-giftoc:
	cd ${WRKSRC} && ${NATIVE_CC} -o giftoc_host giftoc.c
.endif

.include "../../x11/libX11/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
