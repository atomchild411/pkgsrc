# $NetBSD: Makefile,v 1.2 2023/07/04 02:29:15 schmonz Exp $

DISTNAME=		pikchr
PKGVERSION=		1.0.20230526
FOSSIL_TAG=		6d40a5f041311bbe
PKGNAME=		${DISTNAME}-${PKGVERSION}
CATEGORIES=		graphics textproc
MASTER_SITES=		https://pikchr.org/home/tarball/${FOSSIL_TAG}/
DIST_SUBDIR=		${PKGBASE}-${FOSSIL_TAG}

MAINTAINER=		schmonz@NetBSD.org
HOMEPAGE=		https://pikchr.org/
COMMENT=		PIC-like markup language for diagrams
LICENSE=		0-clause-bsd

WRKSRC=			${WRKDIR}/${PKGBASE}

INSTALLATION_DIRS+=	bin

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/${PKGBASE} ${DESTDIR}${PREFIX}/bin

.include "../../mk/bsd.fast.prefs.mk"
# The build runs lemon (the parser generator) on pikchr.y.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		lemon
SUBST_STAGE.lemon=	pre-build
SUBST_FILES.lemon=	Makefile
SUBST_SED.lemon=	-e 's,^\t$$(CC) $$(CFLAGS) lemon.c -o lemon$$,\t${NATIVE_CC} lemon.c -o lemon,'
.endif

.include "../../mk/bsd.pkg.mk"
