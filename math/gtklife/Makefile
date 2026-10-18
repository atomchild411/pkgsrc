# $NetBSD: Makefile,v 1.62 2026/09/02 19:03:23 wiz Exp $

DISTNAME=	gtklife-5.1
PKGREVISION=	47
CATEGORIES=	math
#MASTER_SITES=	http://ironphoenix.org/tril/gtklife/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://homeforaday.org/gtklife/
COMMENT=	The game of life

GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--with-gtk2
CONFIGURE_ARGS+=	--with-docdir=${PREFIX}/share/doc/gtklife
USE_TOOLS+=		gmake pkg-config
LDFLAGS+=		-lX11	# direct link required by ld v2.22

.include "../../mk/bsd.fast.prefs.mk"
# The build runs create_lookup to write the *_lookup.c tables: build it for
# the build host.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		lookup
SUBST_STAGE.lookup=	pre-configure
SUBST_FILES.lookup=	Makefile.in
SUBST_SED.lookup=	-e 's,^create_lookup: $$(CL_OBJS)$$,create_lookup: create_lookup.c util.c,'
SUBST_SED.lookup+=	-e 's,^\t$$(CC) -o create_lookup $$(CL_OBJS)$$,\t${NATIVE_CC} -o create_lookup create_lookup.c util.c,'
.endif

.include "../../x11/gtk2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
