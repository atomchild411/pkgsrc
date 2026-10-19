# $NetBSD: Makefile,v 1.54 2026/09/02 19:02:03 wiz Exp $

DISTNAME=	fntsample-5.4
PKGREVISION=	10
CATEGORIES=	fonts
MASTER_SITES=	${MASTER_SITE_GITHUB:=eugmes/}
GITHUB_TAG=	release/${PKGVERSION_NOREV}

BLOCKS_TXT=		Blocks-20220122.txt
DISTFILES=		${DEFAULT_DISTFILES} ${BLOCKS_TXT}
SITES.${BLOCKS_TXT}=	-http://unicode.org/Public/UNIDATA/Blocks.txt

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/eugmes/fntsample/
COMMENT=	Make font samples, similar to Unicode charts, showing Unicode coverage
LICENSE=	gnu-gpl-v3

USE_TOOLS+=	pkg-config gmake perl:run msgfmt
USE_CMAKE=	yes

WRKSRC=		${WRKDIR}/${DISTNAME:S/-/-release-/}

REPLACE_PERL=	scripts/pdfoutline.pl scripts/pdf-extract-outline.pl

CMAKE_CONFIGURE_ARGS+=	-DUNICODE_BLOCKS=${WRKDIR}/${BLOCKS_TXT}

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# gen-unicode-blocks turns Blocks.txt into C source: build it for the
# build host.
SUBST_CLASSES+=		genblocks
SUBST_STAGE.genblocks=	pre-configure
SUBST_FILES.genblocks=	src/CMakeLists.txt
SUBST_SED.genblocks=	-e 's,"$$<TARGET_FILE:gen-unicode-blocks>","${WRKDIR}/gen-unicode-blocks",'
SUBST_SED.genblocks+=	-e 's,DEPENDS gen-unicode-blocks,,'
SUBST_MESSAGE.genblocks=	Using a gen-unicode-blocks built for the build host.

pre-configure:
	cd ${WRKSRC}/src && ${NATIVE_CC} -std=gnu99 \
		-o ${WRKDIR}/gen-unicode-blocks gen_unicode_blocks.c read_blocks.c
.endif

.include "../../devel/pango/buildlink3.mk"
.include "../../fonts/fontconfig/buildlink3.mk"
.include "../../graphics/cairo/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
