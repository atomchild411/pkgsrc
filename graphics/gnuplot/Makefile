# $NetBSD: Makefile,v 1.210 2026/09/02 19:02:38 wiz Exp $

DISTNAME=	gnuplot-6.0.5
CATEGORIES+=	graphics
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=gnuplot/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://gnuplot.sourceforge.net/
COMMENT=	Portable interactive, function plotting utility
PKGREVISION=	1
#LICENSE=	gnuplot + BSD

API_VERSION=	${PKGVERSION_NOREV:C/([0-9])\.([0-9])\.([0-9])+/\1.\2/}

CONFLICTS+=		gnuplot-nox11-[0-9]*

USE_LANGUAGES=		c
USE_TOOLS+=		makeinfo pkg-config gmake
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--without-latex
CONFIGURE_ARGS+=	ac_cv_prog_EMACS=
INFO_FILES=		yes
TEST_TARGET=		check

PLIST_SUBST+=		API_VERSION=${API_VERSION}

.include "options.mk"

.include "../../mk/readline.buildlink3.mk"
.if   ${READLINE_TYPE} == "editline"
CONFIGURE_ARGS+=	--with-readline=bsd
.elif ${READLINE_TYPE} == "readline"
CONFIGURE_ARGS+=	--with-readline=gnu
.endif

.include "../../converters/libiconv/buildlink3.mk"
.include "../../mk/curses.buildlink3.mk"

# The help file is made by doc2gih, and the demos' binary data (which is
# not installed) by bf_test, which run while building: cross-compiling,
# copies built with the build host's compiler run instead.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		doc2gih
SUBST_STAGE.doc2gih=	post-configure
SUBST_MESSAGE.doc2gih=	Using the build host's doc2gih.
SUBST_FILES.doc2gih=	docs/Makefile demo/Makefile
SUBST_SED.doc2gih=	-e 's,)\./doc2gih$$(EXEEXT) ,)${WRKDIR}/doc2gih-native ,'
SUBST_SED.doc2gih+=	-e 's,@\.\./src/bf_test$$,@${WRKDIR}/bf_test-native,'
pre-build: gnuplot-native-doc2gih
.PHONY: gnuplot-native-doc2gih
gnuplot-native-doc2gih:
	cd ${WRKSRC}/docs && ${NATIVE_CC} -DHAVE_CONFIG_H -I.. -I../src -I. \
	    -I../term -o ${WRKDIR}/doc2gih-native doc2gih.c termdoc.c
	cd ${WRKSRC}/src && ${NATIVE_CC} -DHAVE_CONFIG_H -I.. -I. \
	    -o ${WRKDIR}/bf_test-native bf_test.c -lm
.endif
.include "../../mk/bsd.pkg.mk"
