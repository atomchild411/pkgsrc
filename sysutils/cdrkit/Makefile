# $NetBSD: Makefile,v 1.22 2025/11/27 10:08:17 wiz Exp $

DISTNAME=	cdrkit-1.1.9
PKGREVISION=	10
CATEGORIES=	sysutils
#MASTER_SITES=	http://cdrkit.org/releases/

MAINTAINER=	pkgsrc-users@NetBSD.org
#HOMEPAGE=	http://cdrkit.org/
COMMENT=	Portable command-line CD/DVD recorder software

CONFLICTS=	cdrtools-[0-9]*

USE_CMAKE=		yes
USE_TOOLS+=		perl:run
USE_LANGUAGES=		c c++
CMAKE_CONFIGURE_ARGS+=	-DMANSUBDIR=${PKGMANDIR}

REPLACE_PERL=	3rd-party/dirsplit/dirsplit

.include "../../mk/bsd.fast.prefs.mk"

# include/CMakeLists.txt runs a bitfield order test (try_run), which a
# cross build cannot: big-endian MIPS allocates bitfields from the high bit.
.if ${USE_CROSS_COMPILE:U:tl} == "yes" && ${OPSYS} == "IRIX"
CMAKE_CONFIGURE_ARGS+=	-DBITFIELDS_HTOL=1
# icedax's FIND_FILE calls would find the build host's soundcard headers.
CMAKE_CONFIGURE_ARGS+=	-DHAVE_SYS_SOUNDCARD_H=HAVE_SYS_SOUNDCARD_H-NOTFOUND
CMAKE_CONFIGURE_ARGS+=	-DHAVE_LINUX_SOUNDCARD_H=HAVE_LINUX_SOUNDCARD_H-NOTFOUND
CMAKE_CONFIGURE_ARGS+=	-DHAVE_LIBOSSAUDIO=HAVE_LIBOSSAUDIO-NOTFOUND
.endif

.include "../../archivers/bzip2/buildlink3.mk"
.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/oss.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
