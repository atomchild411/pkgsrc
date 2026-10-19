# $NetBSD: Makefile,v 1.26 2021/11/18 14:12:48 nia Exp $

DISTNAME=		siod
PKGNAME=		siod-3.0
PKGREVISION=		2
CATEGORIES=		lang
MASTER_SITES=		# ftp://ftp.std.com/pub/gjc/
EXTRACT_SUFX=		.tgz

MAINTAINER=		pkgsrc-users@NetBSD.org
#HOMEPAGE=		http://people.delphi.com/gjc/siod.html
COMMENT=		Small-footprint implementation of the Scheme programming language

CONFLICTS=		siag-[0-9]*

WRKSRC=			${WRKDIR}
MAKE_FILE=		makefile
MAKE_JOBS_SAFE=		no
BUILD_TARGET=		${OPSYS:S/Linux/linux/}
MAKE_ENV+=		CC=${CC:Q}

MKPIE_SUPPORTED=	no
RELRO_SUPPORTED=	no

CPPFLAGS+=		-Dunix=1

# XXX: cannot check as WRKSRC == WRKDIR so paths are stripped
CHECK_SHLIBS_SUPPORTED=	no

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# The command scripts (csiod, http-get, ...) are written by running siod
# on their .smd sources: use a siod built for the build host.
SUBST_CLASSES+=		hostsiod
SUBST_STAGE.hostsiod=	pre-build
SUBST_FILES.hostsiod=	makefile
SUBST_SED.hostsiod=	-e 's|\./siod -v01,-m2|${WRKDIR}/siod-host -v01,-m2|'
SUBST_MESSAGE.hostsiod=	Using a siod built for the build host.

# "install" depends on the distribution files, which include man pages
# formatted with nroff and col (not installed, and neither tool is there).
SUBST_CLASSES+=		instdist
SUBST_STAGE.instdist=	pre-build
SUBST_FILES.instdist=	makefile
SUBST_SED.instdist=	-e 's|^install: $$(DISTFILES)$$|install:|'
SUBST_MESSAGE.instdist=	Not formatting man pages for distribution.

pre-build:
	cd ${WRKSRC} && ${NATIVE_CC} -std=gnu89 -w -Dunix=1 \
		-DSIOD_LIB_DEFAULT=\"${WRKSRC}\" -o ${WRKDIR}/siod-host \
		siod.c slib.c sliba.c trace.c slibu.c md5.c -lm -lcrypt
.endif

REPLACE_INTERPRETER+=	siod
REPLACE.siod.old=	/usr/local/bin/siod
REPLACE.siod.new=	${PREFIX}/bin/siod
REPLACE_FILES.siod=	*.scm

MAKE_ENV.SunOS+=	CPPFLAGS=

post-patch:
	${MV} ${WRKSRC}/siod.man ${WRKSRC}/prefix-siod.man
	${SED} -e 's|@PREFIX@|${PREFIX}|g' ${WRKSRC}/prefix-siod.man > ${WRKSRC}/siod.man

.include "../../databases/sdbm/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
