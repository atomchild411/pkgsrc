# $NetBSD: buildlink3.mk,v 1.15 2022/06/28 11:31:40 wiz Exp $

BUILDLINK_TREE+=	bglibs

.if !defined(BGLIBS_BUILDLINK3_MK)
BGLIBS_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.bglibs+=	bglibs>=2.03
BUILDLINK_ABI_DEPENDS.bglibs?=	bglibs>=2.04nb5
BUILDLINK_PKGSRCDIR.bglibs?=	../../devel/bglibs

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# Packages using bglibs install with bg-installer: the build machine's.
TOOL_DEPENDS+=		bglibs>=2.03:../../devel/bglibs
TOOLS_CREATE+=		bg-installer
TOOLS_PATH.bg-installer=	${TOOLBASE}/bin/bg-installer
.endif
.endif # BGLIBS_BUILDLINK3_MK

BUILDLINK_TREE+=	-bglibs
