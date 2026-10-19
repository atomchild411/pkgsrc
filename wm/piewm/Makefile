# $NetBSD: Makefile,v 1.17 2026/01/22 08:37:39 wiz Exp $

DISTNAME=	piewm-1.04
CATEGORIES=	wm
#MASTER_SITES=	http://www.crynwr.com/piewm/

MAINTAINER=	pkgsrc-users@NetBSD.org
#HOMEPAGE=	http://www.crynwr.com/piewm/
COMMENT=	Minimalist window manager based on tvtwm with pie menus

USE_IMAKE=	yes
USE_TOOLS+=	lex:run yacc

# imake's sgi.cf defines SVR4, and <X11/Xthreads.h> then wants UI threads
# (<thread.h>), which IRIX lacks: its pthread branch is right.
BUILDLINK_TRANSFORM.IRIX+=	rm:-DSVR4

.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libXmu/buildlink3.mk"
.include "../../x11/libXpm/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.include "../../x11/xbitmaps/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
