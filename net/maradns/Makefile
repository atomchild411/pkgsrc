# $NetBSD: Makefile,v 1.29 2019/10/06 12:52:20 nia Exp $

DISTNAME=	maradns-2.0.17
CATEGORIES=	net
MASTER_SITES=	https://maradns.samiam.org/download/2.0/${PKGVERSION_NOREV}/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	ddeus.pkgsrc@mailnull.com
HOMEPAGE=	https://maradns.samiam.org/
COMMENT=	Secure DNS server for *NIX systems
LICENSE=	2-clause-bsd

USE_TOOLS+=	awk:build

HAS_CONFIGURE=		yes
PTHREAD_OPTS+=		require
PTHREAD_AUTO_VARS=	yes
MAKE_ENV+=		LANGUAGE="en"

INSTALLATION_DIRS=	bin ${PKGMANDIR}/man1 ${PKGMANDIR}/man5 \
			${PKGMANDIR}/man8 sbin share/examples

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# RandomPrime and make_32bit_tables, run at build time to write headers,
# are for the build host.
SUBST_CLASSES+=		randprime
SUBST_STAGE.randprime=	pre-configure
SUBST_FILES.randprime=	deadwood-*/src/Makefile rng/Makefile
SUBST_SED.randprime=	-e 's|^	\$$(CC) -O3 -o RandomPrime RandomPrime.c|	${NATIVE_CC} -O3 -o RandomPrime RandomPrime.c|'
SUBST_SED.randprime+=	-e 's|^	\$$(CC) -o make_32bit_tables make_32bit_tables.c|	${NATIVE_CC} -o make_32bit_tables make_32bit_tables.c|'
.endif

.include "../../mk/pthread.buildlink3.mk"
LDFLAGS+=	${PTHREAD_LIBS}

SUBST_CLASSES+=		sysconf
SUBST_STAGE.sysconf=	pre-configure
SUBST_VARS.sysconf=	PKG_SYSCONFDIR
SUBST_FILES.sysconf=	parse/ParseMaraRc.c MaraDns.h deadwood-3.2.14/src/DwMain.c

.include "options.mk"

post-install:
	cd ${DESTDIR}${PREFIX}/share/doc/maradns && ${MV} examples ../../examples/maradns

.include "../../mk/bsd.pkg.mk"
