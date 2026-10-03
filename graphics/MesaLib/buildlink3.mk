# $NetBSD: buildlink3.mk,v 1.69 2025/03/07 07:00:33 wiz Exp $

BUILDLINK_TREE+=	MesaLib

.if !defined(MESALIB_BUILDLINK3_MK)
MESALIB_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.MesaLib+=	MesaLib>=3.4.2
BUILDLINK_ABI_DEPENDS.MesaLib+=	MesaLib>=21.3.9nb3
BUILDLINK_PKGSRCDIR.MesaLib?=	../../graphics/MesaLib

.include "../../graphics/MesaLib/features.mk"

# See <http://developer.apple.com/qa/qa2007/qa1567.html>.
.if ${X11_TYPE} == "native" && !empty(MACHINE_PLATFORM:MDarwin-[9].*-*)
BUILDLINK_LDFLAGS.MesaLib+=	-Wl,-dylib_file,/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib
.endif

# IRIX's GL is the system's (builtin.mk), with dependencies of its own:
# none of Mesa's. (A builtin package with pkgsrc dependencies under it would
# be built from pkgsrc instead.)
.if ${OPSYS} != "IRIX"
pkgbase:= MesaLib

.include "../../mk/pkg-build-options.mk"

.if ${PKG_BUILD_OPTIONS.MesaLib:Mx11}
.  include "../../x11/libX11/buildlink3.mk"
.  include "../../x11/libXdamage/buildlink3.mk"
.  include "../../x11/libXext/buildlink3.mk"
.  include "../../x11/libXfixes/buildlink3.mk"
.  include "../../x11/libXrandr/buildlink3.mk"
.  include "../../x11/libXxf86vm/buildlink3.mk"
.  include "../../x11/libxcb/buildlink3.mk"
.  include "../../x11/libxshmfence/buildlink3.mk"
.  include "../../x11/xcb-proto/buildlink3.mk"
.  include "../../x11/xorgproto/buildlink3.mk"
.endif

.if ${MESALIB_SUPPORTS_DRI} == "yes"
.  include "../../x11/libdrm/buildlink3.mk"
.endif
.endif # OPSYS != IRIX

.include "../../mk/pthread.buildlink3.mk"
.endif # MESALIB_BUILDLINK3_MK

BUILDLINK_TREE+=	-MesaLib

# IRIX's <GL/gl.h> stops at OpenGL 1.4 and has no <GL/glext.h>: the
# Khronos extension headers, for the programs that include them. After
# MesaLib's tree, so they are the program's dependency: under MesaLib
# they would make the builtin MesaLib one built from pkgsrc.
.if ${OPSYS} == "IRIX"
.  include "../../graphics/khronos-gl-headers/buildlink3.mk"
.endif
