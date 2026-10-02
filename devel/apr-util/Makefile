# $NetBSD: Makefile,v 1.79 2026/08/06 20:02:00 wiz Exp $

DISTNAME=	apr-util-1.6.4
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_APACHE:=apr/}
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://apr.apache.org/
COMMENT=	Apache Portable Runtime utilities
LICENSE=	apache-2.0

USE_LIBTOOL=		yes
USE_TOOLS+=		pkg-config
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--with-apr=${APR_CONFIG}
CONFIGURE_ARGS+=	--with-expat=${BUILDLINK_PREFIX.expat}
CONFIGURE_ARGS+=	--without-gdbm
CONFIGURE_ARGS+=	--without-odbc
CONFIGURE_ARGS+=	--without-sqlite2
PKGCONFIG_OVERRIDE+=	apr-util.pc.in

# Too many differences between configure test and actual usage.
CONFIGURE_ENV.SunOS+=	apu_cv_memset_s=no

# just a list of exported symbols for a library that also starts with shebang
CHECK_INTERPRETER_SKIP=	lib/aprutil.exp

MAKE_ENV+=	WRAPPER_DIR=${WRAPPER_DIR}

# test status as of 1.6.4:
# Failed Tests   		Total	Fail	Failed %
# ===================================================
# testxlate      		    7	   1	 14.29%

.include "../../mk/bsd.prefs.mk"
.include "options.mk"

# A cross build runs the target's apr-1-config, from a copy whose build
# directory (apr_rules.mk and libtool) is the one in the cross destdir.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
APR_CONFIG=	${WRKDIR}/apr-1-config
pre-configure: apr-cross-config
apr-cross-config:
	${RUN}${SED} -e 's|^installbuilddir="|installbuilddir="${_CROSS_DESTDIR}|' \
		${_CROSS_DESTDIR}${BUILDLINK_PREFIX.apr}/bin/apr-1-config \
		> ${APR_CONFIG}
	${RUN}${CHMOD} +x ${APR_CONFIG}
.else
APR_CONFIG=	${BUILDLINK_PREFIX.apr}/bin/apr-1-config
.endif

TEST_TARGET=	test

.include "../../converters/libiconv/buildlink3.mk"
BUILDLINK_API_DEPENDS.apr+=	apr>=1.5.0
.include "../../devel/apr/buildlink3.mk"
.include "../../textproc/expat/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
