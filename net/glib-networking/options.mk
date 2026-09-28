# $NetBSD: options.mk,v 1.2 2020/03/10 22:53:35 wiz Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.glib-networking

PKG_OPTIONS_REQUIRED_GROUPS=	ssl
PKG_OPTIONS_GROUP.ssl=		gnutls openssl

PKG_SUPPORTED_OPTIONS=		gnome libproxy
PKG_SUGGESTED_OPTIONS=		gnutls gnome libproxy

.include "../../mk/bsd.options.mk"

PLIST_VARS+=	gnutls openssl gnome libproxy

###
### SSL support
###
.if !empty(PKG_OPTIONS:Mgnutls)
PLIST.gnutls=	yes
BUILDLINK_API_DEPENDS.gnutls+= gnutls>=3.6.5
.  include "../../security/gnutls/buildlink3.mk"
.  include "../../security/p11-kit/buildlink3.mk"
MESON_ARGS+=	-Dgnutls=enabled
MESON_ARGS+=	-Dopenssl=disabled
.elif !empty(PKG_OPTIONS:Mopenssl)
PLIST.openssl=	yes
.  include "../../security/openssl/buildlink3.mk"
MESON_ARGS+=	-Dopenssl=enabled
MESON_ARGS+=	-Dgnutls=disabled
.endif

# GNOME's proxy settings (gsettings-desktop-schemas).
.if !empty(PKG_OPTIONS:Mgnome)
PLIST.gnome=	yes
.  include "../../sysutils/gsettings-desktop-schemas/buildlink3.mk"
MESON_ARGS+=	-Dgnome_proxy=enabled
.else
MESON_ARGS+=	-Dgnome_proxy=disabled
.endif

# Proxy configuration through libproxy, with its PAC runner service.
.if !empty(PKG_OPTIONS:Mlibproxy)
PLIST.libproxy=	yes
BUILDLINK_API_DEPENDS.libproxy+=	libproxy>=0.4.6
.  include "../../www/libproxy/buildlink3.mk"
MESON_ARGS+=	-Dlibproxy=enabled
.else
MESON_ARGS+=	-Dlibproxy=disabled
.endif
