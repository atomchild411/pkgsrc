# $NetBSD: Makefile,v 1.27 2026/09/02 19:00:49 wiz Exp $

DISTNAME=	gsound-1.0.3
PKGREVISION=	10
CATEGORIES=	audio gnome
MASTER_SITES=	${MASTER_SITE_GNOME:=sources/${PKGBASE}/${PKGVERSION_NOREV:R}/}
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://gitlab.gnome.org/GNOME/gsound
COMMENT=	Small library for playing system sounds
LICENSE=	gnu-lgpl-v2.1

TOOL_DEPENDS+=	glib2-introspection-[0-9]*:../../devel/glib2-introspection

USE_TOOLS+=	pkg-config

PKGCONFIG_OVERRIDE+=	gsound/gsound.pc

.include "../../mk/bsd.prefs.mk"

# gsound-play is Vala over the GIR, and there is no introspection when
# cross-compiling (devel/gobject-introspection/buildlink3.mk).
PLIST_VARS+=		play
.if ${USE_CROSS_COMPILE:U:tl} != "yes"
PLIST.play=		yes
.endif

.include "../../audio/libcanberra/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../devel/gobject-introspection/buildlink3.mk"
.include "../../devel/meson/build.mk"
.include "../../lang/vala/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
