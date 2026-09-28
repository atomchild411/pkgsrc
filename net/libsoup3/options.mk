# $NetBSD: options.mk,v 1.2 2026/09/10 09:41:58 markd Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.libsoup3
PKG_SUPPORTED_OPTIONS=	gssapi introspection
PKG_SUGGESTED_OPTIONS=	introspection

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mgssapi)
.  include "../../mk/krb5.buildlink3.mk"
MESON_ARGS+=	-Dgssapi=enabled
.else
MESON_ARGS+=	-Dgssapi=disabled
.endif

PLIST_VARS+=	introspection
.if !empty(PKG_OPTIONS:Mintrospection)
PLIST.introspection=	yes
TOOL_DEPENDS+=	glib2-introspection-[0-9]*:../../devel/glib2-introspection
BUILDLINK_API_DEPENDS.gobject-introspection+=	gobject-introspection>=0.9.5
BUILDLINK_DEPMETHOD.gobject-introspection=	build
.  include "../../devel/gobject-introspection/buildlink3.mk"
MESON_ARGS+=	-Dintrospection=enabled
.else
MESON_ARGS+=	-Dintrospection=disabled
.endif
