# $NetBSD: Makefile,v 1.25 2026/06/14 12:49:13 nia Exp $

DISTNAME=		libtai-0.60
PKGREVISION=		8
CATEGORIES=		devel
MASTER_SITES=		http://cr.yp.to/libtai/

MAINTAINER=		schmonz@NetBSD.org
HOMEPAGE=		https://cr.yp.to/libtai.html
COMMENT=		Library for storing and manipulating dates and times
LICENSE=		public-domain

FORCE_C_STD=		gnu89

CONFLICTS=		libowfat<0.32nb1

EGDIR=			share/examples/${PKGBASE}

DJB_ERRNO_FIXUP=	leapsecs_read.c

SUBST_CLASSES+=		paths
SUBST_STAGE.paths=	do-configure
SUBST_FILES.paths=	leapsecs.3 leapsecs_read.c
SUBST_VARS.paths=	PKG_SYSCONFDIR

INSTALLATION_DIRS=	bin include lib ${EGDIR}
INSTALLATION_DIRS+=	${PKGMANDIR}/man3

.include "options.mk"

.include "../../mk/bsd.fast.prefs.mk"

post-build:
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# leapsecs.dat is portable (tai_pack is big-endian): make it with a
# leapsecs built for the build host.
	cd ${WRKSRC} && ${NATIVE_CC} -std=gnu89 -o leapsecs.host leapsecs.c \
		caldate_scan.c caldate_mjd.c tai_pack.c && \
		./leapsecs.host < leapsecs.txt > leapsecs.dat
.else
	cd ${WRKSRC} && ./leapsecs < leapsecs.txt > leapsecs.dat
.endif

do-install:
	set -e; cd ${WRKSRC};						\
	for f in *.3; do						\
		${INSTALL_MAN} "$${f}" ${DESTDIR}${PREFIX}/${PKGMANDIR}/man3; \
	done;								\
	for f in easter nowutc leapsecs yearcal; do			\
		${INSTALL_PROGRAM} "$${f}" ${DESTDIR}${PREFIX}/bin;	\
	done;								\
	for f in *.h; do						\
		${INSTALL_DATA} "$${f}" ${DESTDIR}${PREFIX}/include;	\
	done;								\
	for f in libtai.a; do						\
		${INSTALL_DATA} "$${f}" ${DESTDIR}${PREFIX}/lib;		\
	done;								\
	for f in leapsecs.dat leapsecs.txt; do				\
		${INSTALL_DATA} "$${f}" ${DESTDIR}${PREFIX}/${EGDIR};	\
	done

.include "../../mk/djbware.mk"
.include "../../mk/bsd.pkg.mk"
