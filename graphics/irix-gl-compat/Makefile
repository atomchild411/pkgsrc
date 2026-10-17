# $NetBSD$

DISTNAME=	irix-gl-compat-20261017
PKGREVISION=	1
CATEGORIES=	graphics
MASTER_SITES=	# none
DISTFILES=	# none

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	OpenGL 1.3 to 3.0 and extension entry points for IRIX's libGL
LICENSE=	2-clause-bsd

ONLY_FOR_PLATFORM=	IRIX-*-*

NO_CONFIGURE=	yes
USE_LANGUAGES=	c
WRKSRC=		${WRKDIR}

INSTALLATION_DIRS=	lib

# Links against IRIX's own libGL and libGLcore (the sysroot's), not
# through MesaLib's buildlink3.mk, which adds this library to -lGL.
do-extract:
	${CP} ${FILESDIR}/glcompat.c ${FILESDIR}/glcompat.def ${WRKSRC}/
	${CP} ${FILESDIR}/glcompat-extra.def ${WRKSRC}/

do-build:
	cd ${WRKSRC} && ${CC} ${CFLAGS} ${LDFLAGS} -fPIC -shared		\
		-Wl,-soname,libGLcompat.so.1 -o libGLcompat.so.1	\
		glcompat.c -lGL -lGLcore

do-install:
	${INSTALL_LIB} ${WRKSRC}/libGLcompat.so.1 ${DESTDIR}${PREFIX}/lib
	${LN} -sf libGLcompat.so.1 ${DESTDIR}${PREFIX}/lib/libGLcompat.so

.include "../../mk/bsd.pkg.mk"
