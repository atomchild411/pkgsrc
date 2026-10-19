# $NetBSD: Makefile,v 1.18 2025/11/17 11:01:20 wiz Exp $
#

DISTNAME=	pnm2ppa-1.12
CATEGORIES=	print converters graphics
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=pnm2ppa/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://pnm2ppa.sourceforge.net/
COMMENT=	Filter to convert PNM file to PPA used by some HP DJ printer

CONF_FILES=	${PREFIX}/share/examples/pnm2ppa/pnm2ppa.conf \
		${PKG_SYSCONFDIR}/pnm2ppa.conf

INSTALLATION_DIRS=	bin ${PKGMANDIR}/man1 share/doc/pnm2ppa

post-build:
	for f in				\
	${WRKSRC}/docs/en/CALIBRATION.txt	\
	${WRKSRC}/docs/en/COLOR.txt		\
	${WRKSRC}/docs/en/pnm2ppa.1 ;		\
	do					\
		${CP} $$f $$f.orig ;		\
		${SED} 's|/etc/pnm2ppa|${PKG_SYSCONFDIR}/pnm2ppa|g'	\
			$$f.orig > $$f ;	\
	done

post-install:
	cd ${WRKSRC} &&	\
	${INSTALL_DATA} docs/en/CALIBRATION.txt	docs/en/COLOR.txt	\
		${DESTDIR}${PREFIX}/share/doc/pnm2ppa

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# make_hash_ink, run at build time to write hash_ink.c, is for the build host.
SUBST_CLASSES+=		hashink
SUBST_STAGE.hashink=	pre-configure
SUBST_FILES.hashink=	Makefile
SUBST_SED.hashink=	-e 's|^	\$$(CC) \$$(CFLAGS) -o make_hash_ink make_hash_ink.c|	${NATIVE_CC} -std=gnu89 -o make_hash_ink make_hash_ink.c|'
.endif

.include "../../devel/libgetopt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
