# $NetBSD: Makefile,v 1.9 2015/04/26 11:52:19 ryoon Exp $

PERDITION_COMMENT=	UnixODBC user database module
PERDITION_PKGNAME=	odbc
PKGREVISION=		2

CONFIGURE_ARGS+=	--with-odbc-includes=${BUILDLINK_PREFIX.unixodbc}/include
CONFIGURE_ARGS+=	--with-odbc-libs=${BUILDLINK_PREFIX.unixodbc}/lib

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# configure checks the headers with AC_CHECK_FILE, which a cross build
# cannot run: answer it.
CONFIGURE_ENV+=		ac_cv_file_${BUILDLINK_PREFIX.unixodbc:C/[^a-zA-Z0-9_]/_/g}_include_sql_h=yes
CONFIGURE_ENV+=		ac_cv_file_${BUILDLINK_PREFIX.unixodbc:C/[^a-zA-Z0-9_]/_/g}_include_sqlext_h=yes
CONFIGURE_ENV+=		ac_cv_file_${BUILDLINK_PREFIX.unixodbc:C/[^a-zA-Z0-9_]/_/g}_include_sqltypes_h=yes
.endif

USE_TOOLS+=	bash:run
REPLACE_BASH+=	perdition/db/odbc/perditiondb_odbc_makedb

.include "../../databases/unixodbc/buildlink3.mk"
.include "../../devel/libltdl/buildlink3.mk"
.include "../../mail/perdition/Makefile.common"
