# $NetBSD: Makefile,v 1.1 2018/06/07 19:12:19 ryoon Exp $

.include "../../cross/mingw-w64-x86_64-binutils/Makefile.common"

PKGNAME=	mingw-w64-x86_64-${DISTNAME}
COMMENT=	GNU binutils for win64 cross-development

# IRIX: no MinGW GCC there for this to go with.
NOT_FOR_PLATFORM+=	IRIX-*-*

MINGW_TARGET=		${MINGW_W64_64_TARGET}

.include "../../mk/bsd.pkg.mk"
