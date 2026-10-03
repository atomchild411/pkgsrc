# $NetBSD: Makefile,v 1.19 2023/10/19 14:46:00 wiz Exp $

DISTNAME=	jbig2dec-0.20
CATEGORIES=	graphics
MASTER_SITES=	${MASTER_SITE_GITHUB:=ArtifexSoftware/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://jbig2dec.com/
COMMENT=	JBIG2 decoder library
LICENSE=	gnu-agpl-v3

USE_LIBTOOL=	yes
USE_TOOLS+=	autoreconf autoconf automake
GNU_CONFIGURE=	yes

PKGCONFIG_OVERRIDE+=	jbig2dec.pc.in

PYTHON_FOR_BUILD_ONLY=	test

TEST_TARGET=	check

REPLACE_PYTHON+=	test_jbig2dec.py

# autogen.sh ends by running configure with whatever it is given: give it
# the real environment and arguments, or a cross build runs it as a native
# one and it stops ("cannot run C compiled programs").
pre-configure:
	${RUN} cd ${WRKSRC} && ${SETENV} ${CONFIGURE_ENV} ${SH} ./autogen.sh ${CONFIGURE_ARGS}

.include "../../lang/python/application.mk"
.include "../../mk/bsd.pkg.mk"
