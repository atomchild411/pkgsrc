# $NetBSD: Makefile,v 1.22 2026/01/04 13:39:09 adam Exp $

DISTNAME=	quesoglc-0.7.2-free
PKGNAME=	${DISTNAME:S/-free$//}
CATEGORIES=	graphics
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=quesoglc/}
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://quesoglc.sourceforge.net/
COMMENT=	Free implementation of the OpenGL Character Renderer (GLC)
LICENSE=	gnu-lgpl-v2.1

WRKSRC=		${WRKDIR}/quesoglc-${PKGVERSION_NOREV}

USE_LANGUAGES=		c c++
USE_TOOLS+=		pkg-config gmake
USE_LIBTOOL=		yes
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--disable-executables
# Use vendored fribidi and glew, as the latest are incompatible.
CONFIGURE_ARGS+=	--without-fribidi
CONFIGURE_ARGS+=	--without-glew
PKGCONFIG_OVERRIDE=	quesoglc.pc.in

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "Darwin"
CONFIGURE_ARGS+=	--with-apple-opengl-framework
.else
.include "../../graphics/MesaLib/buildlink3.mk"
#.include "../../graphics/glew/buildlink3.mk"
.include "../../graphics/glu/buildlink3.mk"
.include "../../graphics/freeglut/buildlink3.mk"
.endif

#.include "../../converters/fribidi/buildlink3.mk"
.include "../../fonts/fontconfig/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
# The bundled GLEW provides the GL extensions; keep khronos-gl-headers'
# <GL/glext.h> (guard __gl_glext_h_, which GLEW 1.x does not know) out.
CPPFLAGS.IRIX+=	-D__gl_glext_h_

.include "../../mk/bsd.pkg.mk"
