# $NetBSD: Makefile,v 1.13 2026/09/02 19:02:41 wiz Exp $

DISTNAME=	gts-0.7.6
PKGREVISION=	8
CATEGORIES=	graphics
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gts/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://gts.sourceforge.net/
COMMENT=	GNU Triangulated Surface Library
LICENSE=	gnu-gpl-v2

USE_LIBTOOL=		yes
USE_TOOLS+=		gmake pkg-config
GNU_CONFIGURE=		yes
# it is not necessary to configure libtool
CONFIGURE_ARGS+=	--with-tags=""
PKGCONFIG_OVERRIDE+=	gts.pc.in

CPPFLAGS+=	-I${BUILDLINK_PREFIX.netpbm}/include/netpbm

.include "../../mk/bsd.prefs.mk"

# The build makes predicates_init.h by running predicates_init, which
# works out IEEE double error bounds, the same on the build host: in a
# cross build, build and run it there first.
.if ${USE_CROSS_COMPILE:tl} == "yes"
pre-build: gts-predicates-init
.PHONY: gts-predicates-init
gts-predicates-init:
	${RUN} cd ${WRKSRC}/src &&					\
	${NATIVE_CC} -I. -I.. -o predicates_init predicates_init.c &&	\
	./predicates_init > predicates_init.h
.endif

.include "../../devel/glib2/buildlink3.mk"
.include "../../graphics/netpbm/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
