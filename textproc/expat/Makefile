# $NetBSD: Makefile,v 1.68 2026/08/31 18:16:39 wiz Exp $

DISTNAME=	expat-2.8.4
PKGREVISION=	2
CATEGORIES=	textproc
MASTER_SITES=	${MASTER_SITE_GITHUB:=libexpat/}
GITHUB_PROJECT=	libexpat
GITHUB_RELEASE=	R_${PKGVERSION_NOREV:S/./_/g}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://libexpat.github.io/
COMMENT=	XML parser library written in C
LICENSE=	mit

USE_LANGUAGES=		c c++
USE_LIBTOOL=		yes
USE_TOOLS+=		bash:test
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--without-docbook
CONFIGURE_ARGS+=	--without-examples
CONFIGURE_ARGS+=	--without-tests
# workaround suggested by upstream; xmlwf.1 is in tarball, so docbook not needed
CONFIGURE_ENV+=		DOCBOOK_TO_MAN=false

# IRIX has /dev/urandom but no getrandom or arc4random, and a cross build
# cannot see the file, so name the entropy source; IRIX's open() has no
# O_CLOEXEC flag.
CPPFLAGS.IRIX+=		-DXML_DEV_URANDOM -DO_CLOEXEC=0

# Its CMake package (made by configure, from the Linux template on IRIX)
# names the library libexpat.so.SO_MAJOR.SO_MINOR.SO_PATCH as libtool does
# on Linux; IRIX's libtool names it libexpat.so.2.4, and CMake consumers
# (gdal-lib) failed on the missing file. Point it at the libexpat.so link.
.include "../../mk/bsd.fast.prefs.mk"
.if ${OPSYS} == "IRIX"
SUBST_CLASSES+=		cmakelib
SUBST_STAGE.cmakelib=	post-configure
SUBST_MESSAGE.cmakelib=	Pointing the CMake package at libexpat.so.
SUBST_FILES.cmakelib=	cmake/autotools/expat-noconfig.cmake
SUBST_SED.cmakelib=	-e 's,libexpat\.so\.[0-9]*\.[0-9]*\.[0-9]*",libexpat.so",g'
.endif

TEST_TARGET=	check
REPLACE_BASH=	test-driver-wrapper.sh
# we can't use cmake due to a cyclic dependency
#USE_CMAKE=	yes

PKGCONFIG_OVERRIDE+=	expat.pc.in

DOCDIR=	${PREFIX}/share/doc/expat

post-install:
	${INSTALL_DATA_DIR} ${DESTDIR}${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/reference.html ${DESTDIR}${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/style.css ${DESTDIR}${DOCDIR}

.include "../../mk/bsd.pkg.mk"
