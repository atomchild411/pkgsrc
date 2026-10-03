# $NetBSD$

BUILDLINK_TREE+=	khronos-gl-headers

.if !defined(KHRONOS_GL_HEADERS_BUILDLINK3_MK)
KHRONOS_GL_HEADERS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.khronos-gl-headers+=	khronos-gl-headers>=21.3.9
BUILDLINK_PKGSRCDIR.khronos-gl-headers?=	../../graphics/khronos-gl-headers
BUILDLINK_DEPMETHOD.khronos-gl-headers?=	build
.endif	# KHRONOS_GL_HEADERS_BUILDLINK3_MK

BUILDLINK_TREE+=	-khronos-gl-headers
