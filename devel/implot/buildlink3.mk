# $NetBSD$

BUILDLINK_TREE+=	implot

.if !defined(IMPLOT_BUILDLINK3_MK)
IMPLOT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.implot+=	implot>=1.1
BUILDLINK_ABI_DEPENDS.implot+=	implot>=1.1
BUILDLINK_PKGSRCDIR.implot?=	../../devel/implot

.include "../../devel/imgui/buildlink3.mk"
.endif	# IMPLOT_BUILDLINK3_MK

BUILDLINK_TREE+=	-implot
