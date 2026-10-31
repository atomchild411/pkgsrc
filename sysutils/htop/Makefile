# $NetBSD: Makefile,v 1.38 2026/04/29 16:10:16 fox Exp $

DISTNAME=	htop-3.5.1
PKGREVISION=	2
CATEGORIES=	sysutils
MASTER_SITES=	${MASTER_SITE_GITHUB:=htop-dev/}
GITHUB_RELEASE=	${PKGVERSION_NOREV}
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	nia@NetBSD.org
HOMEPAGE=	https://htop.dev/
COMMENT=	Enhanced version of top utility
LICENSE=	gnu-gpl-v2

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes
USE_CURSES=	getmouse

.include "options.mk"

# IRIX: upstream has no IRIX platform and falls back to "unsupported",
# which shows no processes or meters. files/irix is one (procfs
# PIOCPSINFO, sysmp, swapctl); the configure.ac and Makefile.am patches
# wire it in, so configure is regenerated.
.if ${OPSYS} == "IRIX"
USE_TOOLS+=	autoconf automake autoreconf

post-extract:
	${CP} -R ${FILESDIR}/irix ${WRKSRC}/irix

pre-configure:
	cd ${WRKSRC} && autoreconf -fi
.endif

.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../mk/bsd.pkg.mk"
