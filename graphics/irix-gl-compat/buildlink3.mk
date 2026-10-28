# $NetBSD$

BUILDLINK_TREE+=	irix-gl-compat

.if !defined(IRIX_GL_COMPAT_BUILDLINK3_MK)
IRIX_GL_COMPAT_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.irix-gl-compat+=	irix-gl-compat>=20261017
BUILDLINK_ABI_DEPENDS.irix-gl-compat+=	irix-gl-compat>=20261017nb2
BUILDLINK_PKGSRCDIR.irix-gl-compat?=	../../graphics/irix-gl-compat
# Only libGLcompat: lib/libGL.so is the run-time shim (see the Makefile);
# builds link IRIX's own libGL.
BUILDLINK_CONTENTS_FILTER.irix-gl-compat=	${EGREP} '/libGLcompat\.so'
.endif	# IRIX_GL_COMPAT_BUILDLINK3_MK

BUILDLINK_TREE+=	-irix-gl-compat
