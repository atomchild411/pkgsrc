# $NetBSD: Makefile,v 1.9 2023/06/06 12:42:25 riastradh Exp $
#

.include "../../textproc/mecab/Makefile.common"

DISTNAME=	mecab-ipadic-2.7.0-20070610
PKGNAME=	mecab-ipadic-2.7.0.20070610
PKGREVISION=	1

COMMENT=	Japanese Morphological Dictionary for MeCab
#LICENSE=	# See ${WRKSRC}/COPYING

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# The compiled dictionary depends on the byte order: build it with the
# target's mecab-dict-index, run through the irix-exec bridge (the
# mecab-config from the target's mecab-base names it).
BUILD_DEPENDS+=	mecab-base-[0-9]*:../../textproc/mecab-base
.include "../../mk/irix-exec-bridge.mk"
.else
TOOL_DEPENDS+=	mecab-base-[0-9]*:../../textproc/mecab-base
.endif

GNU_CONFIGURE=	yes

CONFIGURE_ARGS+=	--with-charset=${MECAB_CHARSET:Q}

BUILD_DEFS+=		MECAB_CHARSET

CONFIGURE_ARGS+=	--with-mecab-config=${LOCALBASE}/bin/mecab-config

.include "../../mk/bsd.pkg.mk"
