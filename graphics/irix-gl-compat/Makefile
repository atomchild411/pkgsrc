# $NetBSD$

DISTNAME=	irix-gl-compat-20261017
PKGREVISION=	2
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

# lib/libGL.so: what pkgsrc programs load as libGL.so (their RPATH puts
# ${PREFIX}/lib before /usr/lib32). It defines nothing; it loads pkgsrc's
# libX11 and libXext, then IRIX's libXext and libGL by their paths:
# - IRIX's libGL needs IRIX's libX11.so.1, and rld binds each symbol to the
#   first object loaded that defines it; pkgsrc's Xlib must come first, or
#   XOpenDisplay goes to IRIX's and hangs;
# - IRIX's libGL needs "libXext.so" for _XSGISetSpecialDestroyHandler and
#   XSGIMiscQueryExtension, which ${PREFIX}/lib/libXext.so would shadow.
# The stubs only give the DT_NEEDED entries their absolute paths. The
# buildlink3.mk keeps this libGL.so out of builds, which link IRIX's.
do-build:
	cd ${WRKSRC} && ${CC} ${CFLAGS} ${LDFLAGS} -fPIC -shared		\
		-Wl,-soname,libGLcompat.so.1 -o libGLcompat.so.1	\
		glcompat.c -lGL -lGLcore
	cd ${WRKSRC} && ${ECHO} "/* empty */" > empty.c &&		\
	${CC} -shared -Wl,-soname,/usr/lib32/libXext.so -o stub-Xext.so	\
		empty.c &&						\
	${CC} -shared -Wl,-soname,/usr/lib32/libGL.so -o stub-GL.so empty.c && \
	${CC} ${CFLAGS} ${LDFLAGS} -fPIC -shared -Wl,-soname,libGLshim.so	\
		-Wl,--no-as-needed -o libGL-shim.so empty.c		\
		-l:libX11.so.6 -l:libXext.so.6 ./stub-Xext.so ./stub-GL.so

do-install:
	${INSTALL_LIB} ${WRKSRC}/libGLcompat.so.1 ${DESTDIR}${PREFIX}/lib
	${LN} -sf libGLcompat.so.1 ${DESTDIR}${PREFIX}/lib/libGLcompat.so
	${INSTALL_LIB} ${WRKSRC}/libGL-shim.so ${DESTDIR}${PREFIX}/lib/libGL.so

.include "../../x11/libX11/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
