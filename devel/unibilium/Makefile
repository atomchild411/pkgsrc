# $NetBSD: Makefile,v 1.3 2022/07/25 11:12:24 wiz Exp $

DISTNAME=	unibilium-2.1.1
PKGREVISION=	2
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=neovim/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/neovim/unibilium
COMMENT=	Basic terminfo library
LICENSE=	gnu-lgpl-v3

USE_LIBTOOL=	yes
USE_TOOLS+=	gmake perl

MAKE_FLAGS+=	PREFIX=${PREFIX}
MAKE_FLAGS+=	MANDIR=${PREFIX}/${PKGMANDIR}

PKGCONFIG_OVERRIDE+=	unibilium.pc.in

.include "../../mk/bsd.prefs.mk"

# The default terminfo search path comes from the build host's
# ncurses*-config, which is wrong in a cross build: name IRIX's (pkgsrc's
# ncurses and the system's own).
.if ${OPSYS} == "IRIX"
MAKE_FLAGS+=	TERMINFO_DIRS=\"${PREFIX}/share/terminfo:/usr/share/lib/terminfo\"
.endif

.include "../../mk/bsd.pkg.mk"
