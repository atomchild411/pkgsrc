# $NetBSD: buildlink3.mk,v 1.37 2026/09/02 19:01:26 wiz Exp $

BUILDLINK_TREE+=	glib2

.if !defined(GLIB2_BUILDLINK3_MK)
GLIB2_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.glib2+=	glib2>=2.4.0
BUILDLINK_ABI_DEPENDS.glib2+=	glib2>=2.88.3nb1
BUILDLINK_PKGSRCDIR.glib2?=	../../devel/glib2
BUILDLINK_INCDIRS.glib2+=	include/glib-2.0
BUILDLINK_INCDIRS.glib2+=	include/gio-unix-2.0
BUILDLINK_INCDIRS.glib2+=	lib/glib-2.0/include

TOOL_DEPENDS+=	glib2-tools-[0-9]*:../../devel/glib2-tools

.include "../../mk/bsd.fast.prefs.mk"

# In a cross build these would be the target's programs, first in PATH
# ahead of the build host's from glib2-tools.
.if ${USE_CROSS_COMPILE:U:tl} != "yes"
BUILDLINK_FILES.glib2+=		bin/glib-compile-resources
BUILDLINK_FILES.glib2+=		bin/glib-compile-schemas
.endif

# Meson's gnome module runs the tools glib-2.0's and gio-2.0's .pc files
# name, which in a cross build are target programs: name the build host's
# in meson's cross file instead, and in what pkg-config answers for those
# variables (meson checks them, gsettings-desktop-schemas for one).
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
.  for _t_ in glib-mkenums glib-genmarshal glib-compile-resources glib-compile-schemas
MESON_BINARIES+=	${_t_}
MESON_BINARY.${_t_}=	${TOOLBASE}/bin/${_t_}
.  endfor
.  for _pc_ _t_ in GLIB_2_0 glib-mkenums GLIB_2_0 glib-genmarshal \
	GLIB_2_0 gobject-query GIO_2_0 glib-compile-resources \
	GIO_2_0 glib-compile-schemas GIO_2_0 gdbus-codegen
ALL_ENV+=	PKG_CONFIG_${_pc_}_${_t_:tu:S/-/_/g}=${TOOLBASE}/bin/${_t_}
.  endfor
.endif

.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/libffi/buildlink3.mk"
.include "../../devel/pcre2/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.endif # GLIB2_BUILDLINK3_MK

BUILDLINK_TREE+=	-glib2
