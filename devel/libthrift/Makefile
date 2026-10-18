# $NetBSD: Makefile,v 1.105 2026/08/24 08:42:15 adam Exp $

PKGREVISION= 3
.include "../../devel/thrift/Makefile.common"

PKGNAME=	lib${DISTNAME}
COMMENT=	C++ bindings for the Apache Thrift RPC system

DEPENDS+=	thrift-[0-9]*:../../devel/thrift
BUILD_DIRS=	lib/cpp

TOOLS_BROKEN+=	perl

CONFIGURE_ARGS+=	--without-go # puts garbage into Makefile
CONFIGURE_ARGS+=	--without-rs # puts garbage into Makefile
CONFIGURE_ARGS+=	--enable-tests=no
CONFIGURE_ENV+=		THRIFT=${PREFIX}/bin/thrift
CONFIGURE_ENV+=		ac_cv_prog_PERL= # none, not needed
PKGCONFIG_OVERRIDE=	lib/cpp/thrift-nb.pc.in
PKGCONFIG_OVERRIDE+=	lib/cpp/thrift-z.pc.in
PKGCONFIG_OVERRIDE+=	lib/cpp/thrift.pc.in

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# configure skips its signed right shift test when cross-compiling, and the
# installed TCompactProtocol.tcc then refuses to compile: clang's is
# arithmetic everywhere.
SUBST_CLASSES+=		rshift
SUBST_STAGE.rshift=	post-configure
SUBST_MESSAGE.rshift=	Recording an arithmetic signed right shift.
SUBST_FILES.rshift=	lib/cpp/src/thrift/config.h
SUBST_SED.rshift=	-e 's,^/\* \#undef ARITHMETIC_RIGHT_SHIFT \*/$$,\#define ARITHMETIC_RIGHT_SHIFT 1,'
SUBST_SED.rshift+=	-e 's,^/\* \#undef LOGICAL_RIGHT_SHIFT \*/$$,\#define LOGICAL_RIGHT_SHIFT 2,'
SUBST_SED.rshift+=	-e 's,^/\* \#undef UNKNOWN_RIGHT_SHIFT \*/$$,\#define UNKNOWN_RIGHT_SHIFT 3,'
SUBST_SED.rshift+=	-e 's,^/\* \#undef SIGNED_RIGHT_SHIFT_IS \*/$$,\#define SIGNED_RIGHT_SHIFT_IS 1,'
.endif

.include "../../mk/atomic64.mk"
.include "../../devel/boost-headers/buildlink3.mk"
.include "../../devel/boost-libs/buildlink3.mk"
.include "../../devel/libevent/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
