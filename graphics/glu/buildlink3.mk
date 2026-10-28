# $NetBSD: buildlink3.mk,v 1.35 2013/05/16 05:25:02 richard Exp $

BUILDLINK_TREE+=	glu

.include "../../mk/bsd.fast.prefs.mk"

.if !defined(GLU_BUILDLINK3_MK)
GLU_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.glu+=	glu>=3.4.2
BUILDLINK_ABI_DEPENDS.glu+=	glu>=7.11.2
BUILDLINK_PKGSRCDIR.glu?=	../../graphics/glu

.if ${OPSYS} != "IRIX"
.include "../../graphics/MesaLib/buildlink3.mk"
.endif
.endif # GLU_BUILDLINK3_MK

BUILDLINK_TREE+=	-glu

# IRIX: GLU is the system's (builtin.mk). MesaLib's buildlink3.mk adds the
# pkgsrc irix-gl-compat there; inside glu's subtree that forced glu to
# pkgsrc (and a dependency on the glu package), so include it after.
.if ${OPSYS} == "IRIX"
.include "../../graphics/MesaLib/buildlink3.mk"
.endif
