# $NetBSD$

BUILDLINK_TREE+=	irix-gl-compat

.if !defined(IRIX_GL_COMPAT_BUILDLINK3_MK)
IRIX_GL_COMPAT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.irix-gl-compat+=	irix-gl-compat>=20261017
BUILDLINK_PKGSRCDIR.irix-gl-compat?=	../../graphics/irix-gl-compat
.endif	# IRIX_GL_COMPAT_BUILDLINK3_MK

BUILDLINK_TREE+=	-irix-gl-compat
