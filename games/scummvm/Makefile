# $NetBSD: Makefile,v 1.141 2026/09/02 19:02:22 wiz Exp $

DISTNAME=	scummvm-2026.3.0
PKGREVISION=	2
CATEGORIES=	games
MASTER_SITES=	https://www.scummvm.org/frs/scummvm/${PKGVERSION_NOREV}/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	adam@NetBSD.org
HOMEPAGE=	https://www.scummvm.org/
COMMENT=	LucasArts Script Creation Utility for Maniac Mansion
LICENSE=	gnu-gpl-v2

USE_CXX_FEATURES=	c++11
USE_LANGUAGES=		c c++
USE_TOOLS+=		gmake
HAS_CONFIGURE=		yes
CONFIGURE_ARGS+=	--disable-debug
CONFIGURE_ARGS+=	--disable-optimizations
CONFIGURE_ARGS+=	--disable-seq-midi # not portable
CONFIGURE_ARGS+=	--enable-release
CONFIGURE_ARGS+=	--mandir=${PREFIX}/${PKGMANDIR}
CONFIGURE_ARGS+=	--prefix=${PREFIX}

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# configure only cross-compiles (tests the compiler without running its
# output) when told the host.
CONFIGURE_ARGS+=	--host=${MACHINE_GNU_PLATFORM}
.endif
# Its IRIX branch links libmd, which the IRIX sysroot has not; scummvm
# has its own MD5.
.if ${OPSYS} == "IRIX"
SUBST_CLASSES+=		libmd
SUBST_STAGE.libmd=	pre-configure
SUBST_MESSAGE.libmd=	Not linking libmd on IRIX.
SUBST_FILES.libmd=	configure
SUBST_SED.libmd=	-e 's,"-lmd -lfastm -lm","-lfastm -lm",'
.endif

UNLIMIT_RESOURCES=	datasize
EXTRACT_USING=		bsdtar

CHECK_PORTABILITY_SKIP+=	dists/engine-data/testbed-audiocd-files/image/image-gen.sh
CHECK_PORTABILITY_SKIP+=	dists/opendingux/scummvm.sh

BUILDLINK_API_DEPENDS.zlib+=	zlib>=1.2.1
.include "../../audio/faad2/buildlink3.mk"
.include "../../audio/flac/buildlink3.mk"
.include "../../audio/fluidsynth/buildlink3.mk"
.include "../../audio/liba52/buildlink3.mk"
.include "../../audio/libmad/buildlink3.mk"
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../converters/fribidi/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/giflib/buildlink3.mk"
.include "../../graphics/glew/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../multimedia/libmpeg2/buildlink3.mk"
.include "../../multimedia/libtheora/buildlink3.mk"
.include "../../net/SDL2_net/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
