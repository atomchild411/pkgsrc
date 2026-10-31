# $NetBSD$

.include "../../audio/libao/Makefile.common"

PKGNAME=	${DISTNAME:S/libao/libao-irix/}

COMMENT+=	(IRIX audio plugin)

ONLY_FOR_PLATFORM=	IRIX-*-*

# The plugin talks to the IRIX Audio Library (libaudio's ALwritesamps and
# friends); Makefile.common keeps configure from looking for it.
CONFIGURE_ENV:=		${CONFIGURE_ENV:S/ac_cv_lib_audio_ALwritesamps=no//1}
BUILD_DIRS=		src/plugins/irix
INSTALL_DIRS=		src/plugins/irix

BUILDLINK_API_DEPENDS.libao+=	libao>=0.8.6nb1

_LIBAO_BUILDING_PLUGIN=	yes

.include "../../audio/libao/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
