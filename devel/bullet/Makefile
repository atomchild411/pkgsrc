# $NetBSD: Makefile,v 1.17 2025/08/20 11:34:50 wiz Exp $

DISTNAME=	bullet-2.89
PKGREVISION=	2
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=bulletphysics/}
GITHUB_PROJECT=	bullet3
GITHUB_TAG=	${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://bulletphysics.org/wordpress/
COMMENT=	Collision detection, soft body and rigid body dynamics library
LICENSE=	mit

USE_TOOLS+=	pkg-config
USE_CMAKE=	yes
USE_LANGUAGES=	c c++

CMAKE_CONFIGURE_ARGS+=	-DCMAKE_BUILD_TYPE:STRING=Release
CMAKE_CONFIGURE_ARGS+=	-DBUILD_SHARED_LIBS:BOOL=on
# doesn't install anything without this
CMAKE_CONFIGURE_ARGS+=	-DINSTALL_LIBS:BOOL=on

CMAKE_CONFIGURE_ARGS+=	-DBUILD_BULLET2_DEMOS:BOOL=off
CMAKE_CONFIGURE_ARGS+=	-DBUILD_CPU_DEMOS:BOOL=off
CMAKE_CONFIGURE_ARGS+=	-DBUILD_OPENGL3_DEMOS:BOOL=off
CMAKE_CONFIGURE_ARGS+=	-DBUILD_UNIT_TESTS:BOOL=off
CMAKE_CONFIGURE_ARGS+=	-DCMAKE_POLICY_VERSION_MINIMUM=3.5
# thread-safe, with the multithreaded world (btDiscreteDynamicsWorldMt)
# and Bullet's own pthread task scheduler
CMAKE_CONFIGURE_ARGS+=	-DBULLET2_MULTITHREADING:BOOL=ON

PKGCONFIG_OVERRIDE+=	bullet.pc.in

.include "../../mk/bsd.prefs.mk"

# Static libraries too, for programs that link Bullet in: each shared
# library's objects (position-independent, fine in an archive), archived
# with the archiver CMake found. bullet.pc gets what a static link needs.
post-install:
	set -e; cache=`find ${WRKSRC} -name CMakeCache.txt | head -1`;	\
	ar=`${SED} -n 's/^CMAKE_AR:FILEPATH=//p' $$cache`;			\
	for so in ${DESTDIR}${PREFIX}/lib/lib*.so; do				\
		name=`basename $$so .so`; name=$${name#lib};			\
		dir=`find ${WRKSRC} -type d -name $$name.dir -path '*/CMakeFiles/*' | head -1`; \
		test -n "$$dir";						\
		find $$dir -name '*.o' | sort |					\
		    xargs $$ar rcs ${DESTDIR}${PREFIX}/lib/lib$$name.a;	\
	done
	${ECHO} 'Libs.private: -lpthread -lm' >> ${DESTDIR}${PREFIX}/lib/pkgconfig/bullet.pc
.if ${OPSYS} != "Darwin"
.include "../../graphics/MesaLib/buildlink3.mk"
.include "../../graphics/glu/buildlink3.mk"
.endif
.include "../../mk/bsd.pkg.mk"
