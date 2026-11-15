# $NetBSD$

DISTNAME=	implot-1.1
CATEGORIES=	devel graphics
MASTER_SITES=	${MASTER_SITE_GITHUB:=epezent/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/epezent/implot
COMMENT=	Immediate mode plotting library for Dear ImGui
LICENSE=	mit

USE_LANGUAGES=		c c++
USE_CXX_FEATURES+=	c++11
USE_LIBTOOL=		yes

MAKE_FILE=	Makefile.pkgsrc
MAKE_FLAGS+=	PREFIX=${PREFIX} VERSION=${PKGVERSION_NOREV}
MAKE_FLAGS+=	LIBTOOL=${LIBTOOL:Q}
MAKE_FLAGS+=	IMGUI_INCDIR=${BUILDLINK_PREFIX.imgui}/include/imgui

post-extract:
	${CP} ${FILESDIR}/Makefile.pkgsrc ${WRKSRC}/

.include "../../devel/imgui/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
