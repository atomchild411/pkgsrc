# $NetBSD: Makefile,v 1.21 2026/09/02 19:01:05 wiz Exp $
#

DISTNAME=		libredwg-0.12.4
PKGREVISION=		13
CATEGORIES=		cad
MASTER_SITES=		${MASTER_SITE_GNU:=libredwg/}
EXTRACT_SUFX=		.tar.xz

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://www.gnu.org/software/libredwg
COMMENT=		Free library to read/write DWG files
LICENSE=		gnu-gpl-v3

GNU_CONFIGURE=		yes
USE_LANGUAGES=		c
USE_LIBTOOL=		yes
USE_TOOLS+=		makeinfo perl:test

CONFIGURE_ARGS+=	--infodir=${PREFIX}/${PKGINFODIR}
CONFIGURE_ARGS+=	--disable-bindings
# No gperf: the distribution has its output, and configure's version parse
# (${GPERF_VERSION:2:1}) needs bash, so with a gperf on the PATH /bin/sh
# leaves "3.3", which "#if GPERF_VERSION < 301" rejects.
CONFIGURE_ENV+=		ac_cv_prog_GPERF=

INFO_FILES=		yes

# IRIX has no sanitizers: "all" builds the standalone fuzzer example, which
# asks for AddressSanitizer; build it without.
SUBST_CLASSES.IRIX+=	noasan
SUBST_STAGE.noasan=	pre-configure
SUBST_MESSAGE.noasan=	No sanitizers for the fuzzer example.
SUBST_FILES.noasan=	examples/Makefile.in
SUBST_SED.noasan=	-e 's/-DSTANDALONE -DHAVE_ASAN /-DSTANDALONE /'
SUBST_SED.noasan+=	-e 's/-fsanitize=address,undefined //'

TEST_TARGET=		check

.include "../../devel/pcre2/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"		# test target
.include "../../textproc/py-libxml2/buildlink3.mk"	# test target
.include "../../print/pslib/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
