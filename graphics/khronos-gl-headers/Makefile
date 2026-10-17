# $NetBSD$

DISTNAME=	mesa-21.3.9
PKGNAME=	khronos-gl-headers-21.3.9
PKGREVISION=	1
CATEGORIES=	graphics
MASTER_SITES=	https://mesa.freedesktop.org/archive/
EXTRACT_SUFX=	.tar.xz
DISTINFO_FILE=	${.CURDIR}/../../graphics/MesaLib/distinfo

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://registry.khronos.org/OpenGL/
COMMENT=	OpenGL extension headers (glext.h, glxext.h, khrplatform.h)
LICENSE=	mit

# For systems whose OpenGL is their own and predates these headers (IRIX).
# No CONFLICTS with MesaLib: there it is the builtin one (no files), which
# a bulk build registers as installed.

EXTRACT_ELEMENTS=	${DISTNAME}/include/GL/glext.h
EXTRACT_ELEMENTS+=	${DISTNAME}/include/GL/glxext.h
EXTRACT_ELEMENTS+=	${DISTNAME}/include/KHR/khrplatform.h

NO_CONFIGURE=	yes
NO_BUILD=	yes
USE_LANGUAGES=	# none

INSTALLATION_DIRS=	include/GL include/KHR

.include "../../mk/bsd.prefs.mk"

# IRIX: a <GL/gl.h> and a <GL/glx.h> that are IRIX's with what Mesa's add
# (files/gl.h, files/glx.h): the pointer types of the extensions IRIX's
# declare, then <GL/glext.h> and <GL/glxext.h>, as code written for Mesa
# expects.
PLIST_VARS+=		glwrapper
.if ${OPSYS} == "IRIX"
PLIST.glwrapper=	yes
.endif

do-install:
	${INSTALL_DATA} ${WRKSRC}/include/GL/glext.h ${WRKSRC}/include/GL/glxext.h \
		${DESTDIR}${PREFIX}/include/GL
	${INSTALL_DATA} ${WRKSRC}/include/KHR/khrplatform.h \
		${DESTDIR}${PREFIX}/include/KHR
.if ${OPSYS} == "IRIX"
	${INSTALL_DATA} ${FILESDIR}/gl.h ${FILESDIR}/glx.h \
		${DESTDIR}${PREFIX}/include/GL
.endif

.include "../../mk/bsd.pkg.mk"
