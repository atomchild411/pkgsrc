# $NetBSD: buildlink3.mk,v 1.1 2024/08/10 23:47:57 js Exp $

BUILDLINK_TREE+=	objfw

.if !defined(OBJFW_BUILDLINK3_MK)
OBJFW_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.objfw+=	objfw>=1.1
BUILDLINK_ABI_DEPENDS.objfw+=	objfw>=1.1
BUILDLINK_PKGSRCDIR.objfw?=	../../devel/objfw

# A cross meson finds config tools only in its cross file: name objfw-config
# (a shell script, which the build host runs), as configure scripts find it.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
MESON_BINARIES+=		objfw-config
MESON_BINARY.objfw-config=	objfw-config
.endif
.endif

BUILDLINK_TREE+=	-objfw
