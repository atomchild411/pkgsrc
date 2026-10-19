# $NetBSD: Makefile,v 1.21 2026/09/02 19:03:49 wiz Exp $

DISTNAME=	smpeg2-2.0.0
PKGREVISION=	18
CATEGORIES=	multimedia
MASTER_SITES=	http://www.libsdl.org/projects/smpeg/release/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.libsdl.org/projects/smpeg/
COMMENT=	Free MPEG1 video player library with sound support
LICENSE=	gnu-lgpl-v2.1

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes
USE_LANGUAGES=	c c++

CONFIGURE_ARGS+=	--program-suffix=2

# smpeg2-config runs sdl2-config: the installed one, not the one configure
# found on the build PATH (pkgsrc's tools directory).
SUBST_CLASSES+=		sdlconfig
SUBST_STAGE.sdlconfig=	pre-configure
SUBST_MESSAGE.sdlconfig=	Naming the installed sdl2-config.
SUBST_FILES.sdlconfig=	smpeg2-config.in
SUBST_SED.sdlconfig=	-e 's,@SDL_CONFIG@,${PREFIX}/bin/sdl2-config,g'

.include "../../mk/bsd.fast.prefs.mk"

LDFLAGS.SunOS+=	-lsocket -lnsl

post-install:
	${MV} ${DESTDIR}${PREFIX}/bin/smpeg2-config2 \
		${DESTDIR}${PREFIX}/bin/smpeg2-config

.include "../../devel/SDL2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
