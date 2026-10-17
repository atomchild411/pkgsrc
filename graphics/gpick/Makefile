# $NetBSD: Makefile,v 1.61 2026/09/02 19:02:38 wiz Exp $

DISTNAME=	gpick-0.3
PKGREVISION=	13
CATEGORIES=	graphics
MASTER_SITES=	${MASTER_SITE_GITHUB:=thezbyg/}
GITHUB_RELEASE=	v${PKGVERSION_NOREV}

MAINTAINER=	ryoon@NetBSD.org
HOMEPAGE=	https://github.com/thezbyg/gpick/
COMMENT=	Advanced color picker
LICENSE=	modified-bsd

USE_LANGUAGES=	c c++
USE_TOOLS+=	gmake pkg-config msgfmt msgmerge xgettext

USE_CXX_FEATURES+=	filesystem

TOOL_DEPENDS+=	ragel-[0-9]*:../../devel/ragel

CXXFLAGS+=	-Wno-sign-compare
LDFLAGS+=	-llua

.include "../../devel/boost-libs/buildlink3.mk"
.include "../../devel/cmake/build.mk"
# IRIX: the executable's own path is where it is installed (Paths.cpp).
SUBST_CLASSES.IRIX+=	prefix
SUBST_STAGE.prefix=	pre-configure
SUBST_FILES.prefix=	source/Paths.cpp
SUBST_VARS.prefix=	PREFIX

# luaL_requiref, luaL_setfuncs: Lua 5.2 or later.
LUA_VERSIONS_INCOMPATIBLE=	51
.include "../../lang/lua/buildlink3.mk"
.include "../../x11/gtk3/buildlink3.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../textproc/expat/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
