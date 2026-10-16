# $NetBSD: Makefile,v 1.47 2026/08/24 08:42:30 adam Exp $

DISTNAME=		clucene-core-2.3.3.4
PKGNAME=		lib${DISTNAME:S/-core-/-/}
PKGREVISION=		30
CATEGORIES=		textproc
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=clucene/}

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://clucene.sourceforge.net/index.php/Main_Page
COMMENT=		Text search engine written in C++
LICENSE=		gnu-lgpl-v2.1 OR apache-2.0

PKGCONFIG_OVERRIDE+=	libclucene-core.pc.in

USE_LANGUAGES=	c c++
USE_LIBTOOL=	yes

CMAKE_CONFIGURE_ARGS+=	-DBUILD_CONTRIBS_LIB=ON
# https://sourceforge.net/p/clucene/bugs/236/
CMAKE_CONFIGURE_ARGS+=	-DCMAKE_POLICY_VERSION_MINIMUM=3.5
# Results of the run checks, which a cross build cannot run (only cross
# builds read these).
CMAKE_CONFIGURE_ARGS+=	-DLUCENE_STATIC_CONSTANT_SYNTAX_EXITCODE=0
CMAKE_CONFIGURE_ARGS+=	-D_CL_HAVE_GCC_ATOMIC_FUNCTIONS_EXITCODE=0
CMAKE_CONFIGURE_ARGS+=	-D_CL_HAVE_NAMESPACES_EXITCODE=0
CMAKE_CONFIGURE_ARGS+=	-D_CL_HAVE_NO_SNPRINTF_BUG_EXITCODE=0
CMAKE_CONFIGURE_ARGS+=	-D_CL_HAVE_PTHREAD_MUTEX_RECURSIVE_EXITCODE=0
CMAKE_CONFIGURE_ARGS+=	-D_CL_HAVE_TRY_BLOCKS_EXITCODE=0

.include "../../devel/cmake/build.mk"
.include "../../devel/boost-libs/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
