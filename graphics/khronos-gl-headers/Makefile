# $NetBSD$

DISTNAME=	mesa-21.3.9
PKGNAME=	khronos-gl-headers-21.3.9
CATEGORIES=	graphics
MASTER_SITES=	https://mesa.freedesktop.org/archive/
EXTRACT_SUFX=	.tar.xz
DISTINFO_FILE=	${.CURDIR}/../../graphics/MesaLib/distinfo

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://registry.khronos.org/OpenGL/
COMMENT=	OpenGL extension headers (glext.h, glxext.h, khrplatform.h)
LICENSE=	mit

# For systems whose OpenGL is their own and predates these headers (IRIX):
# Mesa installs the same files.
CONFLICTS+=	MesaLib-[0-9]*

EXTRACT_ELEMENTS=	${DISTNAME}/include/GL/glext.h
EXTRACT_ELEMENTS+=	${DISTNAME}/include/GL/glxext.h
EXTRACT_ELEMENTS+=	${DISTNAME}/include/KHR/khrplatform.h

NO_CONFIGURE=	yes
NO_BUILD=	yes
USE_LANGUAGES=	# none

INSTALLATION_DIRS=	include/GL include/KHR

do-install:
	${INSTALL_DATA} ${WRKSRC}/include/GL/glext.h ${WRKSRC}/include/GL/glxext.h \
		${DESTDIR}${PREFIX}/include/GL
	${INSTALL_DATA} ${WRKSRC}/include/KHR/khrplatform.h \
		${DESTDIR}${PREFIX}/include/KHR

.include "../../mk/bsd.pkg.mk"
