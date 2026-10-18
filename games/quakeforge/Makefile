# $NetBSD: Makefile,v 1.75 2026/07/13 04:35:56 wiz Exp $

DISTNAME=		quakeforge-0.7.2
PKGREVISION=		36
CATEGORIES=		games
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=quake/}

MAINTAINER=		snj@NetBSD.org
HOMEPAGE=		http://www.quakeforge.net/
COMMENT=		Improved Quake engine
LICENSE=		gnu-gpl-v2

CONFIGURE_ARGS+=	--enable-xdg
CONFIGURE_ARGS+=	--with-cpp=${CPP:Q}" %d %i %o"
GNU_CONFIGURE=		YES
USE_LANGUAGES=		c c++
USE_TOOLS+=		bison flex gmake pkg-config
USE_LIBTOOL=		YES

SUBST_CLASSES+=		dsp
SUBST_STAGE.dsp=	pre-configure
SUBST_MESSAGE.dsp=	Adjusting sound device path.
SUBST_FILES.dsp=	libs/audio/targets/snd_oss.c
SUBST_SED.dsp=		-e "s|/dev/dsp|${DEVOSSAUDIO}|"

LIBS+=			${BUILDLINK_LDADD.oss}

REPLACE_PYTHON+=	tools/qfcc/source/qfpreqcc

.include "../../mk/bsd.prefs.mk"

# configure cannot test the byte order when cross-compiling: name it.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
.  include "../../mk/endian.mk"
CONFIGURE_ARGS+=	--with-endian=${MACHINE_ENDIAN}
# No libcdaudio (nor libmediad, libds) in the IRIX sysroot.
CONFIGURE_ENV+=		qf_cv_sgi_cd=no
.endif
# Its IRIX sound output (snd_sgi.c) no longer builds; SDL's plays sound
# on IRIX instead.
CONFIGURE_ENV.IRIX+=	ac_cv_header_dmedia_audio_h=no

PLIST_VARS+=		sunaudio linux
.if ${OPSYS} == "NetBSD" || ${OPSYS} == "SunOS"
PLIST.sunaudio=		yes
.endif

.if ${OPSYS} == "Linux"
PLIST.linux=		yes
.endif

INSTALLATION_DIRS=	include/QF/GL include/QF/plugin include/QF/ruamoko/gui

.include "options.mk"
.include "../../lang/python/application.mk"
.include "../../audio/flac/buildlink3.mk"
.include "../../audio/libsamplerate/buildlink3.mk"
.include "../../audio/libvorbis/buildlink3.mk"
.include "../../audio/libwildmidi/buildlink3.mk"
.include "../../devel/SDL/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libXxf86dga/buildlink3.mk"
.include "../../x11/libXxf86vm/buildlink3.mk"
.include "../../x11/xorgproto/buildlink3.mk"
.include "../../mk/oss.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
