# $NetBSD: Makefile,v 1.1 2018/06/07 19:25:17 ryoon Exp $

.include "../../cross/mingw-w64-x86_64-binutils/Makefile.common"

PKGNAME=	mingw-w64-i686-${DISTNAME}
COMMENT=	GNU binutils for win32 cross-development

# IRIX: no MinGW GCC there for this to go with.
NOT_FOR_PLATFORM+=	IRIX-*-*

MINGW_TARGET=		${MINGW_W64_32_TARGET}

.include "../../mk/bsd.pkg.mk"
