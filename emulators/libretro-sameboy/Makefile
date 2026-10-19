# $NetBSD: Makefile,v 1.9 2026/09/21 07:47:21 wiz Exp $

.include "../../emulators/sameboy/Makefile.common"

PKGNAME=	libretro-${DISTNAME}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://docs.libretro.com/library/sameboy/
COMMENT=	Libretro core based on the SameBoy Game Boy/Game Boy Color emulator

BUILD_TARGET=	libretro

LIBRETRO_CORE=	sameboy
MAKE_JOBS_SAFE=	no

# The boot ROMs are turned into C with hexdump, which is not a pkgsrc
# tool: use the (POSIX) od branch upstream has for Haiku.
SUBST_CLASSES+=		od
SUBST_STAGE.od=		pre-build
SUBST_FILES.od=		libretro/Makefile
SUBST_SED.od=		-e 's|^ifneq (\$$(findstring Haiku.*|ifeq (,)|'
SUBST_MESSAGE.od=	Using od instead of hexdump.

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# pb12 compresses the boot ROM logo during the build.
MAKE_FLAGS+=	NATIVE_CC=${NATIVE_CC:Q}
.endif

.include "../../emulators/retroarch/core.mk"
.include "../../mk/bsd.pkg.mk"
