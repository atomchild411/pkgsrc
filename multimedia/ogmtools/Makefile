# $NetBSD: Makefile,v 1.16 2023/10/02 10:58:33 rhialto Exp $
#

DISTNAME=	ogmtools-1.5
PKGREVISION=	3
CATEGORIES=	multimedia
MASTER_SITES=	https://www.bunkus.org/videotools/ogmtools/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.bunkus.org/videotools/ogmtools/
COMMENT=	Ogg Media files manipulation tools

USE_LANGUAGES=	c c++
FORCE_CXX_STD=	c++11
GNU_CONFIGURE=	YES

CONFIGURE_ARGS+=	--with-dvdread-includes=${BUILDLINK_DIR:Q}

# AC_CHECK_FILE cannot look when cross-compiling: the header is in buildlink.
CONFIGURE_ENV+=		ac_cv_file_${BUILDLINK_DIR:C/[^A-Za-z0-9]/_/g}_include_dvdread_dvd_reader_h=yes

CPPFLAGS.SunOS+=	-Du_int16_t=uint16_t -Du_int32_t=uint32_t -Du_int64_t=uint64_t

.include "../../audio/libvorbis/buildlink3.mk"
.include "../../multimedia/libdvdread/buildlink3.mk"
.include "../../multimedia/libogg/buildlink3.mk"

.include "../../mk/bsd.pkg.mk"
