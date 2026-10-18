# $NetBSD: Makefile,v 1.17 2021/04/23 23:44:38 wiz Exp $

DISTNAME=	p2c-1.20
PKGREVISION=	1
CATEGORIES=	lang
#MASTER_SITES=	ftp://csvax.cs.caltech.edu/pub/
EXTRACT_SUFX=	.tar.Z

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	Pascal to C compiler (translates Pascal to C)
LICENSE=	gnu-gpl-v1

WRKSRC=		${WRKDIR}/src
CFLAGS+=	-Dunix=1

.include "../../mk/bsd.prefs.mk"

# The build runs makeproto to write p2c.proto and p2c.hdrs: build it for
# the build host.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		makeproto
SUBST_STAGE.makeproto=	pre-build
SUBST_FILES.makeproto=	Makefile
SUBST_SED.makeproto=	-e 's,^\t$$(CC) $$(CFLAGS) $$(LFLAGS) makeproto.c -o makeproto$$,\t${NATIVE_CC} -std=gnu89 makeproto.c -o makeproto,'
.endif

post-extract:
	# The distfile contains a number of world-writable files, including
	# an entry for '.' that causes pkgsrc to become upset. Fix it.
	${CHMOD} 755 ${WRKDIR}
	${CHMOD} -R o-w ${WRKDIR}/*

.include "../../mk/bsd.pkg.mk"
