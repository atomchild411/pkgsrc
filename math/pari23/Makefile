# $NetBSD: Makefile,v 1.20 2026/06/14 19:20:40 nia Exp $

DISTNAME=	pari-2.3.5
PKGREVISION=	33
CATEGORIES=	math
MASTER_SITES=	http://pari.math.u-bordeaux.fr/pub/pari/OLD/2.3/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://pari.math.u-bordeaux.fr/
COMMENT=	Software package for computer-aided number theory (2.3 version)
LICENSE=	gnu-gpl-v2

MAKE_JOBS_SAFE=	no

USE_LIBTOOL=		yes
USE_TOOLS+=		perl
USE_LANGUAGES+=		c c++

# Tons of problems compiling with newer language versions.
# Uses "old-style function definitions".
FORCE_C_STD=		gnu89

HAS_CONFIGURE=		yes
CONFIGURE_ENV+=		LOCALBASE=${LOCALBASE}
CONFIGURE_ENV+=		PERL5=${PERL5:Q}
# config/get_double_format's answer, which cross builds cannot run: IRIX
# n32 keeps a double's sign and exponent in l[0]; n64 has a 64-bit long.
CONFIGURE_ENV.IRIX+=	cross_doubleformat=${ABI:U32:S/64/-/:S/32/0/}

CONFIGURE_SCRIPT=	${WRKSRC}/Configure
CONFIGURE_ARGS+=	--prefix=${PREFIX}
CONFIGURE_ARGS+=	--mandir=${PREFIX}/${PKGMANDIR}/man1
CONFIGURE_ARGS+=	--share-prefix=${PREFIX}/share

REPLACE_PERL+=		src/desc/PARI/822.pm

BUILD_TARGET=		all
TEST_TARGET=		test-compat bench
INSTALL_TARGET=		install

SUBST_CLASSES+=		fix-cfg
SUBST_STAGE.fix-cfg=	pre-configure
SUBST_MESSAGE.fix-cfg=	Adding CFLAGS to Configure scripts.
SUBST_FILES.fix-cfg=	config/get_*
SUBST_SED.fix-cfg=	-e 's,$$CC $$extraflag,$$CC $$CFLAGS $$extraflag,g'

# pari.cfg records the ranlib Configure found, which is pkgsrc's wrapper.
SUBST_CLASSES+=		cfg-tools
SUBST_STAGE.cfg-tools=	post-install
SUBST_MESSAGE.cfg-tools=	Removing tool wrapper paths from pari.cfg.
SUBST_FILES.cfg-tools=	${DESTDIR}${PREFIX}/lib/pari/pari.cfg
SUBST_SED.cfg-tools=	-e 's,${TOOLS_DIR}/bin/,,g'

.include "options.mk"

.include "../../devel/ncurses/buildlink3.mk"
# rl_save_prompt()
.include "../../devel/readline/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
