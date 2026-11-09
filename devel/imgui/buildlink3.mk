# $NetBSD$

BUILDLINK_TREE+=	imgui

.if !defined(IMGUI_BUILDLINK3_MK)
IMGUI_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.imgui+=	imgui>=1.92.9b
BUILDLINK_ABI_DEPENDS.imgui+=	imgui>=1.92.9b
BUILDLINK_PKGSRCDIR.imgui?=	../../devel/imgui

.include "../../devel/SDL2/buildlink3.mk"
.include "../../graphics/MesaLib/buildlink3.mk"
.include "../../graphics/glfw/buildlink3.mk"
.endif	# IMGUI_BUILDLINK3_MK

BUILDLINK_TREE+=	-imgui
