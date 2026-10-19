# $NetBSD: Makefile,v 1.25 2026/06/07 18:26:20 wiz Exp $

DISTNAME=	wayland-protocols-1.49
CATEGORIES=	devel
MASTER_SITES=	https://gitlab.freedesktop.org/wayland/wayland-protocols/-/releases/${PKGVERSION_NOREV}/downloads/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://wayland.freedesktop.org/
COMMENT=	Additional wayland functionality
LICENSE=	mit

USE_TOOLS+=		pkg-config

MESON_ARGS+=		-Dtests=false

PKGCONFIG_OVERRIDE+=	wayland-protocols.pc.in

.include "../../mk/bsd.prefs.mk"

.if ${USE_CROSS_COMPILE:tl} == "yes"
# wayland-protocols runs wayland-scanner at build-time, but gets the
# path via pkg-config, and pkg-config -- helpfully describing the
# target system instead of the native system -- returns a full path
# under PREFIX while we need it to be under TOOLBASE, so we have to set
# up a meson cross binary with the whole PREFIX-qualified original
# pathname.
TOOL_DEPENDS+=				wayland>=0:../../devel/wayland
MESON_BINARIES+=			wayland_scanner
MESON_BINARY_KEY.wayland_scanner=	${PREFIX}/bin/wayland-scanner
MESON_BINARY.wayland_scanner=		${TOOLBASE}/bin/wayland-scanner
# The wayland-scanner dependency is a build-machine (native) one, looked
# up with pkg-config: point meson at the build machine's .pc files.
MAKE_ENV+=	PKG_CONFIG_PATH_FOR_BUILD=${TOOLBASE}/lib/pkgconfig
.endif

.include "../../devel/meson/build.mk"
# Without the tests only the (build machine's) wayland-scanner is used;
# IRIX has no wayland (no epoll, no kqueue for epoll-shim).
.if ${OPSYS} != "IRIX"
.include "../../devel/wayland/buildlink3.mk"
.endif
.include "../../mk/bsd.pkg.mk"
