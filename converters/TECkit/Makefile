# $NetBSD: Makefile,v 1.17 2025/12/21 14:33:00 wiz Exp $

DISTNAME=	TECkit-2.5.13
CATEGORIES=	converters
MASTER_SITES=	${MASTER_SITE_GITHUB:=silnrsi/}
GITHUB_PROJECT=	teckit
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	minskim@NetBSD.org
HOMEPAGE=	https://github.com/silnrsi/teckit/
COMMENT=	Low-level toolkit to perform encoding conversions
LICENSE=	gnu-lgpl-v2.1 OR cpl-1.0

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes
USE_LANGUAGES=	c c++
USE_TOOLS+=	aclocal autoconf automake gmake

USE_CXX_FEATURES=	c++11

PKGCONFIG_OVERRIDE=	teckit.pc.in

# IRIX's <sys/types.h> has a uchar_t of its own (unsigned char), which
# UtfCodec.h's (uint32_t, used in it alone) clashes with.
SUBST_CLASSES.IRIX+=	uchar
SUBST_STAGE.uchar=	pre-configure
SUBST_MESSAGE.uchar=	Renaming UtfCodec.h's uchar_t, which IRIX's <sys/types.h> has.
SUBST_FILES.uchar=	SFconv/UtfCodec.h
SUBST_SED.uchar=	-e 's/\([^A-Za-z0-9_]\)uchar_t\([^A-Za-z0-9_]\)/\1utf_uchar_t\2/g'

pre-configure:
	cd ${WRKSRC} && libtoolize -c && aclocal && \
	    autoheader && autoconf && automake -a

.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
