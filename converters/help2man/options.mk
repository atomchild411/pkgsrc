# $NetBSD: options.mk,v 1.2 2025/05/06 10:10:01 jperkin Exp $

PKG_OPTIONS_VAR=	PKG_OPTIONS.help2man
PKG_SUPPORTED_OPTIONS=	nls
# nls builds bindtextdomain.so, an LD_PRELOAD shim that needs RTLD_NEXT
# (IRIX has none).
.if ${OPSYS} != "IRIX"
PKG_SUGGESTED_OPTIONS+=	nls
.endif
PLIST_VARS+=		nls

.include "../../mk/bsd.options.mk"

.if !empty(PKG_OPTIONS:Mnls)
USE_TOOLS+=		msgfmt
PLIST.nls=		yes
CONFIGURE_ARGS+=	--enable-nls
.else
CONFIGURE_ARGS+=	--disable-nls
.endif
