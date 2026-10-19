# $NetBSD: Makefile,v 1.10 2026/02/22 08:15:07 wiz Exp $

DISTNAME=	xxkb-1.11-src
PKGNAME=	${DISTNAME:S/-src//}
CATEGORIES=	x11
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=xxkb/}

MAINTAINER=	cheusov@NetBSD.org
HOMEPAGE=	https://sourceforge.net/projects/xxkb/
COMMENT=	XXKB - switches and indicates a current keyboard layout
LICENSE=	artistic

USE_TOOLS+=		xmkmf
USE_IMAKE=		yes
DOC_FILES=		LICENSE README.koi8 README
DOC_DIR=		${PREFIX}/share/doc/${PKGBASE}
INSTALLATION_DIRS=	${DOC_DIR}

MAKE_FLAGS+=		MANPATH=${PREFIX}/${PKGMANDIR}

WRKSRC=			${WRKDIR}/xxkb

post-install:
.for i in ${DOC_FILES}
	${INSTALL_DATA} ${WRKSRC}/${i} ${DESTDIR}${DOC_DIR}
.endfor

# imake's sgi.cf defines SVR4, and <X11/Xthreads.h> then wants UI threads
# (<thread.h>), which IRIX lacks: its pthread branch is right.
BUILDLINK_TRANSFORM.IRIX+=	rm:-DSVR4

.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libXpm/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
