# $NetBSD: Makefile,v 1.12 2025/11/17 11:00:37 wiz Exp $

DISTNAME=		libnjb-2.2.7
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=libnjb/}

MAINTAINER=		ku3@sl.aanet.ru
HOMEPAGE=		https://libnjb.sourceforge.net/
COMMENT=		Communicating with some Creative and Dell audio players
LICENSE=		modified-bsd

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes
USE_TOOLS+=	pkg-config
USE_LANGUAGES+=	c c++

PKGCONFIG_OVERRIDE+=	libnjb.pc.in

# The API documentation is made only where doxygen happens to be on the
# PATH; the PLIST has none.
CONFIGURE_ENV+=	ac_cv_prog_HAVE_DOXYGEN=false

.include "../../mk/curses.buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/libusb.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
