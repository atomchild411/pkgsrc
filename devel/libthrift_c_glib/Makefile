# $NetBSD: Makefile,v 1.15 2026/09/02 19:01:38 wiz Exp $

PKGREVISION= 2
.include "../../devel/thrift/Makefile.common"

PKGNAME=	${DISTNAME:S/thrift/libthrift_c_glib/}
COMMENT=	C (Glib) bindings for the Apache Thrift RPC system

DEPENDS+=	thrift-[0-9]*:../../devel/thrift
BUILD_DIRS=	lib/c_glib

TOOLS_BROKEN+=		perl

CONFIGURE_ARGS+=	--without-go # puts garbage into Makefile
CONFIGURE_ARGS+=	--without-rs # puts garbage into Makefile
CONFIGURE_ENV+=		THRIFT=${PREFIX}/bin/thrift
PKGCONFIG_OVERRIDE=	lib/c_glib/thrift_c_glib.pc.in
# The socket transport calls gethostbyname_r() with glibc's six arguments;
# IRIX's takes five, as Solaris's.
CONFIGURE_ENV.IRIX+=	ac_cv_func_gethostbyname_r=no

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# lib/c_glib/test runs thrift, the target's here, to generate its sources.
MAKE_FLAGS+=		SUBDIRS=.
# configure skips its signed right shift test when cross-compiling, and the
# compact protocol then refuses to compile: clang's is arithmetic everywhere.
SUBST_CLASSES+=		rshift
SUBST_STAGE.rshift=	post-configure
SUBST_MESSAGE.rshift=	Recording an arithmetic signed right shift.
SUBST_FILES.rshift=	lib/c_glib/src/thrift/config.h
SUBST_SED.rshift=	-e 's,^/\* \#undef ARITHMETIC_RIGHT_SHIFT \*/$$,\#define ARITHMETIC_RIGHT_SHIFT 1,'
SUBST_SED.rshift+=	-e 's,^/\* \#undef LOGICAL_RIGHT_SHIFT \*/$$,\#define LOGICAL_RIGHT_SHIFT 2,'
SUBST_SED.rshift+=	-e 's,^/\* \#undef UNKNOWN_RIGHT_SHIFT \*/$$,\#define UNKNOWN_RIGHT_SHIFT 3,'
SUBST_SED.rshift+=	-e 's,^/\* \#undef SIGNED_RIGHT_SHIFT_IS \*/$$,\#define SIGNED_RIGHT_SHIFT_IS 1,'
.endif

.include "../../devel/glib2/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
