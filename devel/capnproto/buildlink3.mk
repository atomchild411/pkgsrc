# $NetBSD: buildlink3.mk,v 1.3 2023/07/19 14:49:45 nia Exp $

BUILDLINK_TREE+=	capnproto

.if !defined(CAPNPROTO_BUILDLINK3_MK)
CAPNPROTO_BUILDLINK3_MK:=

USE_CXX_FEATURES+=	c++14

BUILDLINK_API_DEPENDS.capnproto+=	capnproto>=0.8.0
BUILDLINK_PKGSRCDIR.capnproto?=		../../devel/capnproto

BUILDLINK_FILES.capnproto+=	bin/capnp
BUILDLINK_FILES.capnproto+=	bin/capnpc
BUILDLINK_FILES.capnproto+=	bin/capnpc-c++
BUILDLINK_FILES.capnproto+=	bin/capnpc-capnp

.include "../../mk/bsd.fast.prefs.mk"
# Cross-compiling, schemas are compiled with the build host's capnp, not
# the target's in the buildlink tree (CapnProtoConfig.cmake's
# CAPNP_EXECUTABLE and CAPNPC_CXX_EXECUTABLE are cache variables).
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
TOOL_DEPENDS+=		capnproto-[0-9]*:../../devel/capnproto
CMAKE_CONFIGURE_ARGS+=	-DCAPNP_EXECUTABLE=${TOOLBASE}/bin/capnp
CMAKE_CONFIGURE_ARGS+=	-DCAPNPC_CXX_EXECUTABLE=${TOOLBASE}/bin/capnpc-c++
.endif

.endif	# CAPNPROTO_BUILDLINK3_MK

BUILDLINK_TREE+=	-capnproto
