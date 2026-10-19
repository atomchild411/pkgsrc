# $NetBSD: Makefile,v 1.46 2026/09/02 19:04:01 wiz Exp $

DISTNAME=	ncdc-1.25
PKGREVISION=	1
CATEGORIES=	net
MASTER_SITES=	https://dev.yorhel.nl/download/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://dev.yorhel.nl/ncdc
COMMENT=	Modern and lightweight direct connect client (curses interface)
LICENSE=	mit

USE_TOOLS+=	pkg-config
GNU_CONFIGURE=	yes

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# makeheaders and gendoc, run at build time, are for the build host.
SUBST_CLASSES+=		gendoc
SUBST_STAGE.gendoc=	pre-configure
SUBST_FILES.gendoc=	Makefile.in
SUBST_SED.gendoc=	-e 's|^	\$$(AM_V_CCLD)\$$(LINK) \$$(gendoc_OBJECTS) .*|	${NATIVE_CC} -I. -o $$@ $$(srcdir)/doc/gendoc.c|'
SUBST_SED.gendoc+=	-e 's|^	\$$(AM_V_CCLD)\$$(LINK) \$$(makeheaders_OBJECTS) .*|	${NATIVE_CC} -o $$@ $$(srcdir)/deps/makeheaders.c|'
.endif

.include "../../archivers/bzip2/buildlink3.mk"
.include "../../databases/sqlite3/buildlink3.mk"
BUILDLINK_API_DEPENDS.glib2+=	glib2>=2.32
.include "../../devel/glib2/buildlink3.mk"
.include "../../devel/ncurses/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../security/gnutls/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
