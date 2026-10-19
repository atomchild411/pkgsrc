# $NetBSD: Makefile,v 1.15 2026/09/02 19:02:12 wiz Exp $

DISTNAME=	jumpnbump-1.61
PKGREVISION=	14
CATEGORIES=	games
MASTER_SITES=	https://gitlab.com/LibreGames/jumpnbump/uploads/95acdae2a232513f068e260977371dcf/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://libregames.gitlab.io/jumpnbump/
COMMENT=	Multiplayer platform game with bunnies
LICENSE=	gnu-gpl-v2

USE_TOOLS+=	gmake

CHECK_PORTABILITY_SKIP+=	build-mingw.sh

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# gobpack and jnbpack build the game data (written byte by byte, so
# portable): use copies built for the build host.
SUBST_CLASSES+=		hostpack
SUBST_STAGE.hostpack=	pre-build
SUBST_FILES.hostpack=	data/Makefile
SUBST_SED.hostpack=	-e 's,^GOBPACK = .*,GOBPACK = ${WRKDIR}/host/gobpack,'
SUBST_SED.hostpack+=	-e 's,^JNBPACK = .*,JNBPACK = ${WRKDIR}/host/jnbpack,'
SUBST_MESSAGE.hostpack=	Using gobpack and jnbpack built for the build host.

pre-build:
	${MKDIR} ${WRKDIR}/host
.  for t in gobpack jnbpack
	${NATIVE_CC} -o ${WRKDIR}/host/${t} ${WRKSRC}/modify/${t}.c
.  endfor
.endif

.include "../../archivers/bzip2/buildlink3.mk"
.include "../../audio/SDL2_mixer/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../net/SDL2_net/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
