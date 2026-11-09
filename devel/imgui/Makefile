# $NetBSD$

DISTNAME=	imgui-1.92.9b
CATEGORIES=	devel graphics
MASTER_SITES=	${MASTER_SITE_GITHUB:=ocornut/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/ocornut/imgui
COMMENT=	Bloat-free graphical user interface library for C++
LICENSE=	mit

USE_LANGUAGES=		c c++
USE_CXX_FEATURES+=	c++11
USE_LIBTOOL=		yes

MAKE_FILE=	Makefile.pkgsrc
MAKE_FLAGS+=	PREFIX=${PREFIX} VERSION=${PKGVERSION_NOREV}
MAKE_FLAGS+=	LIBTOOL=${LIBTOOL:Q}

# imgui_impl_sdl2.cpp includes <SDL.h>.
CPPFLAGS+=	-I${BUILDLINK_PREFIX.SDL2}/include/SDL2

post-extract:
	${CP} ${FILESDIR}/Makefile.pkgsrc ${WRKSRC}/

.include "../../devel/SDL2/buildlink3.mk"
.include "../../graphics/MesaLib/buildlink3.mk"
.include "../../graphics/glfw/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
