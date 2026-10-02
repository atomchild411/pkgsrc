# $NetBSD: Makefile,v 1.50 2025/03/30 21:10:42 wiz Exp $

DISTNAME=	mk-configure-0.40.0
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=mk-configure/}

MAINTAINER=	cheusov@NetBSD.org
HOMEPAGE=	https://github.com/cheusov/mk-configure
COMMENT=	Lightweight but powerful replacement for GNU autotools
LICENSE=	modified-bsd

DEPENDS+=	bmake-[0-9]*:../../devel/bmake

USE_LANGUAGES=		c c++
USE_TOOLS=		makeinfo pax

BUILD_TARGET=		all all-doc
INSTALL_TARGET=		install install-doc

MAKE_PROGRAM=		${TOOLBASE}/bin/bmake

MAKE_ENV+=		MANDIR=${PREFIX}/${PKGMANDIR} \
			SYSCONFDIR=${PKG_SYSCONFDIR} \
			BMAKE=${PREFIX}/bin/bmake \
			USE_INSTALL=mkc_install \
			USE_AWK=${AWK:Q} \
			USE_ID=${ID:Q}

# Fix the build on NetBSD 9 since it passes .MAKE.LEVEL.ENV via MAKEFLAGS,
# and the pkgsrc make doesn't allow this variable.
MAKE_ENV+=		MAKEFLAGS=

PLIST_SRC+=		${WRKDIR}/PLIST-addon
PLIST_SRC+=		PLIST

EGDIR=			share/examples/mk-configure
INSTALLATION_DIRS=	${EGDIR}

TEST_TARGET=		test

post-build:
	set -e; cd ${WRKSRC}/mk; \
	${FIND} . -name 'mkc_imp.cc_*' -o -name 'mkc_imp.cxx_*' | \
		${SED} "s;^\([.]/\)*;share/mk-configure/mk/;g" > ${WRKDIR}/PLIST-addon

post-install:
	cd ${WRKSRC}/examples && ${PAX} -wr * ${DESTDIR}${PREFIX}/${EGDIR}
	${INSTALL_DATA} ${WRKSRC}/presentation/*.pdf \
		${DESTDIR}${PREFIX}/share/doc/mk-configure

.include "../../mk/bsd.prefs.mk"

# Cross builds run mkc_compiler_settings, which runs BMAKE, while building:
# the build host's then, and the installed scripts name the target's.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
MAKE_ENV+=		BMAKE=${TOOLBASE}/bin/bmake
SUBST_CLASSES+=		bmake
SUBST_STAGE.bmake=	post-build
SUBST_MESSAGE.bmake=	Naming the target's bmake in the scripts.
SUBST_FILES.bmake=	scripts/mkcmake scripts/mkc_compiler_settings
SUBST_SED.bmake=	-e 's|${TOOLBASE}/bin/bmake|${PREFIX}/bin/bmake|g'
.endif

CHECK_PERMS_SKIP=	*/foobar.in */hello_world3.in */prog1.awk.in

.if ${OPSYS} != NetBSD && ${OPSYS} != FreeBSD && ${OPSYS} != OpenBSD && ${OPSYS} != DragonFly
# non-BSD system
DEPENDS+=	bmkdep-[0-9]*:../../devel/bmkdep
.endif

.include "../../mk/bsd.pkg.mk"
