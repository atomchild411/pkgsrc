# $NetBSD: Makefile,v 1.23 2026/01/19 07:58:15 wiz Exp $

DISTNAME=		discount-2.2.7e
CATEGORIES=		textproc
MASTER_SITES=		https://www.pell.portland.or.us/~orc/Code/discount/
#MASTER_SITES=		${MASTER_SITE_GITHUB:=Orc/}
#GITHUB_TAG=		v${PKGVERSION_NOREV}
EXTRACT_SUFX=		.tar.bz2

MAINTAINER=		schmonz@NetBSD.org
HOMEPAGE=		http://www.pell.portland.or.us/~orc/Code/discount/
COMMENT=		Markdown C implementation
LICENSE=		modified-bsd

WRKSRC=			${WRKDIR}/${PKGNAME_NOREV}

CONFLICTS+=		multimarkdown-[0-9]*

HAS_CONFIGURE=		YES
CONFIGURE_SCRIPT=	./configure.sh
CONFIGURE_ARGS=		--prefix=${PREFIX}
CONFIGURE_ARGS+=	--execdir=${PREFIX}/bin
CONFIGURE_ARGS+=	--libdir=${PREFIX}/lib
CONFIGURE_ARGS+=	--mandir=${PREFIX}/${PKGMANDIR}
CONFIGURE_ARGS+=	--shared
CONFIGURE_ARGS+=	--enable-all-features

USE_LIBTOOL=		yes

PKGCONFIG_OVERRIDE+=	libmarkdown.pc.in

INSTALL_TARGET=		install.everything
TEST_TARGET=		test

.include "../../mk/bsd.fast.prefs.mk"
# configure.inc compiles a helper (config.sed) that it runs for every
# substitution, and the build runs mktags to write blocktags: build both
# for the build host.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		configsed
SUBST_STAGE.configsed=	pre-configure
SUBST_FILES.configsed=	configure.inc
SUBST_SED.configsed=	-e 's,$$AC_CC -o config.sed ngc,${NATIVE_CC} -o config.sed ngc,'
SUBST_CLASSES+=		mktags
SUBST_STAGE.mktags=	pre-configure
SUBST_FILES.mktags=	Makefile.in
SUBST_SED.mktags=	-e 's,^mktags: mktags.o$$,mktags: mktags.c,'
SUBST_SED.mktags+=	-e 's,^\t$$(LINK) -o mktags mktags.o$$,\t${NATIVE_CC} -I. -o mktags mktags.c,'
.endif

.include "../../mk/bsd.pkg.mk"
