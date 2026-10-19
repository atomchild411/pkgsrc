# $NetBSD: Makefile,v 1.3 2020/11/29 19:42:52 nia Exp $
#

.include "../../devel/zookeeper/Makefile.common"

PKGNAME=	lib${DISTNAME}
COMMENT=	Highly reliable distributed coordination C lib

GNU_CONFIGURE=	yes

# generated/zookeeper.jute.c ships in the tarball (AC_CHECK_FILE cannot look when cross-compiling).
CONFIGURE_ENV+=		ac_cv_file_generated_zookeeper_jute_c=yes
CONFIGURE_ENV+=		ac_cv_file_generated_zookeeper_jute_h=yes

USE_LANGUAGES=	c c99
USE_LIBTOOL=	yes

CONFIGURE_DIRS=	src/c

CFLAGS.SunOS+=	-D_POSIX_PTHREAD_SEMANTICS
LIBS.SunOS+=	-lnsl -lsocket

# Tests require c++ and cppunit
#USE_LANGUAGES+=	c++
#TEST_TARGET=		run-check

BUILDLINK_TRANSFORM+=	rm:-Werror

BUILDLINK_DEPMETHOD.cppunit=	build
.include "../../devel/cppunit/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
