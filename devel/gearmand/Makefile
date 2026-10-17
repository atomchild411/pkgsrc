# $NetBSD: Makefile,v 1.85 2026/08/24 08:42:14 adam Exp $

DISTNAME=	gearmand-1.1.19.1
PKGREVISION=	33
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=gearman/}
GITHUB_PROJECT=	gearmand
GITHUB_RELEASE=	${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://gearman.org/
COMMENT=	Gearman C Server and Library
LICENSE=	modified-bsd

GNU_CONFIGURE=	yes
USE_TOOLS+=	gmake pkg-config
USE_LIBTOOL=	yes
USE_LANGUAGES=	c c++

FORCE_CXX_STD=	gnu++11

CONFIGURE_ARGS+=	--enable-jobserver=no
CONFIGURE_ARGS+=	--disable-libdrizzle
CONFIGURE_ARGS+=	--with-boost=${BUILDLINK_PREFIX.boost-libs}

# Cross-building: the libevent checks run a test program.
CONFIGURE_ENV.IRIX+=	ax_cv_libevent=yes ax_cv_libevent2=yes
CONFIGURE_ENV.IRIX+=	ax_cv_libevent2_pthreads=yes
# The working-fnmatch check too; the replacement's header is not shipped.
CONFIGURE_ENV.IRIX+=	ac_cv_func_fnmatch_works=yes
# And the libuuid ones: IRIX's libc has no uuid_generate, pkgsrc's libuuid
# has it and uuid_generate_time_safe.
CONFIGURE_ENV.IRIX+=	ax_cv_libuuid_is_required=yes ax_cv_libuuid_works=yes
CONFIGURE_ENV.IRIX+=	ax_cv_uuid_generate_time_safe=yes
CONFIGURE_ENV.SunOS+=	ax_cv_check_cflags__Werror__pie=no
CONFIGURE_ENV.SunOS+=	ax_cv_check_cxxflags__Werror__pie=no

.include "options.mk"

PKGCONFIG_OVERRIDE+=	support/gearmand.pc.in

.include "../../devel/boost-headers/buildlink3.mk"
.include "../../devel/boost-libs/buildlink3.mk"
.include "../../devel/gperf/buildlink3.mk"
.include "../../devel/libevent/buildlink3.mk"
.include "../../devel/libexecinfo/buildlink3.mk"
.include "../../devel/libuuid/buildlink3.mk"
.include "../../security/libssh2/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
