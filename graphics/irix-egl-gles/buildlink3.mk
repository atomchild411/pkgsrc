# $NetBSD$

BUILDLINK_TREE+=	irix-egl-gles

.if !defined(IRIX_EGL_GLES_BUILDLINK3_MK)
IRIX_EGL_GLES_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.irix-egl-gles+=	irix-egl-gles>=20260928
BUILDLINK_PKGSRCDIR.irix-egl-gles?=	../../graphics/irix-egl-gles

.include "../../graphics/khronos-gl-headers/buildlink3.mk"
.endif	# IRIX_EGL_GLES_BUILDLINK3_MK

BUILDLINK_TREE+=	-irix-egl-gles
