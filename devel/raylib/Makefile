# $NetBSD: Makefile,v 1.6 2026/02/02 23:27:46 wiz Exp $

DISTNAME=	raylib-5.5
PKGREVISION=	1
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=raysan5/}

MAINTAINER=	charlotte@NetBSD.org
HOMEPAGE=	https://www.raylib.com/
COMMENT=	Simple library to enjoy videogames programming
LICENSE=	zlib

USE_LANGUAGES=	c c++

CMAKE_CONFIGURE_ARGS+=	-DPLATFORM=Desktop
CMAKE_CONFIGURE_ARGS+=	-DUSE_EXTERNAL_GLFW:BOOL=ON
CMAKE_CONFIGURE_ARGS+=	-DBUILD_EXAMPLES:BOOL=OFF
CMAKE_CONFIGURE_ARGS+=	-DBUILD_SHARED_LIBS:BOOL=ON

.include "../../mk/bsd.prefs.mk"

# IRIX: SGI's OpenGL is 1.1 or 1.2, below the default renderer's 3.3.
.if ${OPSYS} == "IRIX"
CMAKE_CONFIGURE_ARGS+=	-DOPENGL_VERSION=1.1
.endif

.include "../../devel/cmake/build.mk"
.include "../../graphics/MesaLib/buildlink3.mk"
BUILDLINK_API_DEPENDS.glfw+=	glfw>=3.4
.include "../../graphics/glfw/buildlink3.mk"
# clang predefines mips on IRIX (as gcc did, outside strict modes); the
# sources use it as a name.
CFLAGS.IRIX+=	-Umips
CXXFLAGS.IRIX+=	-Umips

.include "../../mk/bsd.pkg.mk"
