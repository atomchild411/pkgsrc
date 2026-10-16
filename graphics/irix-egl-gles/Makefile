# $NetBSD$

DISTNAME=	irix-egl-gles-20260928
CATEGORIES=	graphics
# No public site yet: the distfile is "git archive --prefix=${DISTNAME}/"
# of the author's repository at 2406e6c, placed in DISTDIR by hand.
MASTER_SITES=	# none
FETCH_MESSAGE=	"${DISTFILES} comes from the irix-egl-gles repository (git archive 2406e6c);"
FETCH_MESSAGE+=	"put it in ${DISTDIR}."

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	EGL 1.4 and OpenGL ES 2.0 on IRIX's own libGL.so and GLX
# LICENSE: not chosen yet by the author. The Khronos headers it builds
# with are under the Khronos (MIT-style) license.

# IRIX's GL only, never Mesa's: graphics/MesaLib is builtin on IRIX
# (IRIX libGL.so with libGLcore.so), with GLX and no EGL or GLES.
ONLY_FOR_PLATFORM=	IRIX-*-*

# IRIX's libGL.so is linked to IRIX's libX11.so.1, and the library hands
# X displays to it: link IRIX's X too (as www/netscape5's irix-motif
# option does), not pkgsrc's libX11.so.6. SGI's link libraries come from
# IRIX_X_NATIVE, laid out as /usr/lib32 (private: never published).
IRIX_X_NATIVE?=		${IRIX_SCRATCH}/irix-x-native
BUILDLINK_PASSTHRU_DIRS+=	${IRIX_X_NATIVE}
LDFLAGS+=		-L${IRIX_X_NATIVE}/usr/lib32

MAKE_FLAGS+=		PREFIX=${PREFIX:Q} RPATH=${PREFIX:Q}/lib GLINC=/usr/include
INSTALL_MAKE_FLAGS+=	DESTDIR=${DESTDIR:Q}

# The Khronos platform header comes from graphics/khronos-gl-headers,
# which installs the same file.
post-install:
	${RM} -f ${DESTDIR}${PREFIX}/include/KHR/khrplatform.h
	${RMDIR} ${DESTDIR}${PREFIX}/include/KHR

.include "../../graphics/khronos-gl-headers/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
