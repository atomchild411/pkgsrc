# $NetBSD: Makefile,v 1.161 2026/09/02 19:02:04 wiz Exp $

PKGREVISION= 2
# GObject introspection in cross builds: g-ir-scanner runs the target's
# programs on the IRIS clones (CROSS_INTROSPECTION).
.include "../../mk/irix-exec-bridge.mk"
.include "Makefile.common"

COMMENT=	OpenType text shaping engine

MESON_ARGS+=	-Ddocs=disabled
# Use external icu support.
MESON_ARGS+=	-Dicu=disabled
MESON_ARGS+=	-Dtests=disabled

.include "../../mk/bsd.pkg.mk"
