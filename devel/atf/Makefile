# $NetBSD: Makefile,v 1.30 2026/09/03 04:41:06 adam Exp $

DISTNAME=	atf-0.25
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=freebsd/}
GITHUB_RELEASE=	${DISTNAME}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/freebsd/atf
COMMENT=	Automated testing framework
LICENSE=	2-clause-bsd

CONFLICTS+=		atf-libs<0.20

USE_CXX_FEATURES=	c++20
USE_LANGUAGES=		c c++
USE_LIBTOOL=		yes
GNU_CONFIGURE=		yes
# Run tests configure cannot do in a cross build: IRIX's getopt takes no GNU '+' prefix.
CONFIGURE_ENV.IRIX+=	kyua_cv_getopt_plus=no
# ... clang has __noreturn__; getcwd(NULL, 0) is not counted on (atf then
# passes its own buffer).
CONFIGURE_ENV.IRIX+=	kyua_cv_attribute_noreturn=yes kyua_cv_getcwd_works=no
CONFIGURE_ARGS+=	ATF_SHELL=${SH:Q}

PKGCONFIG_OVERRIDE=	atf-c/atf-c.pc.in
PKGCONFIG_OVERRIDE+=	atf-c++/atf-c++.pc.in
PKGCONFIG_OVERRIDE+=	atf-sh/atf-sh.pc.in

TEST_TARGET=		check

.include "../../mk/bsd.pkg.mk"
