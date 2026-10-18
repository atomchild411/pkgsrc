# $NetBSD: Makefile,v 1.8 2023/07/13 06:21:47 nia Exp $

DISTNAME=	snowball-2.2.0
PKGNAME=	${DISTNAME:S/snowball/libstemmer/}
PKGREVISION=	1
CATEGORIES=	textproc
MASTER_SITES=	${MASTER_SITE_GITHUB:=snowballstem/}
GITHUB_PROJECT=	snowball
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	ryoon@NetBSD.org
HOMEPAGE=	https://snowballstem.org/
COMMENT=	Snowball compiler and the stemming algorithms
LICENSE=	modified-bsd

USE_TOOLS+=	gmake perl
USE_LIBTOOL=	yes
MAKE_FILE=	GNUmakefile

BUILD_TARGET=	libstemmer.la

INSTALLATION_DIRS+=	include lib

do-install:
	${INSTALL_DATA} ${WRKSRC}/include/libstemmer.h \
		${DESTDIR}${PREFIX}/include
	${LIBTOOL} --quiet --tag=CC --mode=install \
	    ${INSTALL_LIB} ${WRKSRC}/libstemmer.la ${DESTDIR}${PREFIX}/lib

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# The build runs the snowball compiler it builds to write the stemmers' C:
# build one for the build host too, and run that.
SUBST_CLASSES+=		snowball
SUBST_STAGE.snowball=	pre-build
SUBST_MESSAGE.snowball=	Running a build-host snowball.
SUBST_FILES.snowball=	GNUmakefile
SUBST_SED.snowball=	-e 's,^\([[:space:]]*\)\./snowball ,\1${WRKDIR}/snowball-native ,'
pre-build: snowball-native
.PHONY: snowball-native
snowball-native:
	${RUN} cd ${WRKSRC} && ${NATIVE_CC} -O2 -o ${WRKDIR}/snowball-native compiler/*.c
.endif

.include "../../mk/bsd.pkg.mk"
