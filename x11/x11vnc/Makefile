# $NetBSD: Makefile,v 1.107 2026/09/02 19:05:34 wiz Exp $

DISTNAME=	x11vnc-0.9.17
PKGREVISION=	5
CATEGORIES=	x11 net
MASTER_SITES=	${MASTER_SITE_GITHUB:=LibVNC/}
GITHUB_PROJECT=	x11vnc

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/LibVNC/x11vnc
COMMENT=	VNC server for real X displays
LICENSE=	gnu-gpl-v2

USE_TOOLS+=	autoconf automake autoreconf gmake pkg-config
GNU_CONFIGURE=	yes

CFLAGS+=	-Wno-implicit-function-declaration

# The sysroot has IRIX's <X11/extensions/readdisplay.h>, but the X libraries
# are pkgsrc's, without SGI's ReadDisplay extension.
CONFIGURE_ENV.IRIX+=	ac_cv_header_X11_extensions_readdisplay_h=no

.include "options.mk"

pre-configure:
	cd ${WRKSRC} && autoreconf -vif

.include "../../security/openssl/buildlink3.mk"
.include "../../net/libvncserver/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
