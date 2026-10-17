# $NetBSD: buildlink3.mk,v 1.24 2026/09/02 19:03:50 wiz Exp $

BUILDLINK_TREE+=	ORBit2

.if !defined(ORBIT2_BUILDLINK3_MK)
ORBIT2_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.ORBit2+=	ORBit2>=2.12.0
BUILDLINK_ABI_DEPENDS.ORBit2+=	ORBit2>=2.14.19nb8
BUILDLINK_PKGSRCDIR.ORBit2?=	../../net/ORBit2

.include "../../devel/glib2/buildlink3.mk"
.include "../../net/libIDL/buildlink3.mk"

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == yes
# orbit-idl-2 runs at build time: the build machine's, first in PATH and
# as ORBIT_IDL.
TOOL_DEPENDS+=		ORBit2>=2.14.19:../../net/ORBit2
CONFIGURE_ENV+=		ORBIT_IDL=${TOOLBASE}/bin/orbit-idl-2
MAKE_ENV+=		ORBIT_IDL=${TOOLBASE}/bin/orbit-idl-2
buildlink-ORBit2-cookie: buildlink-ORBit2-orbit-idl
.PHONY: buildlink-ORBit2-orbit-idl
buildlink-ORBit2-orbit-idl: buildlink-directories
	${MKDIR} ${BUILDLINK_DIR}/bin
	${LN} -fs ${TOOLBASE}/bin/orbit-idl-2 ${BUILDLINK_DIR}/bin/orbit-idl-2
.endif
.endif # ORBIT2_BUILDLINK3_MK

BUILDLINK_TREE+=	-ORBit2
