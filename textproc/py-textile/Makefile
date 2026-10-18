# $NetBSD: Makefile,v 1.31 2026/05/11 05:41:46 adam Exp $

DISTNAME=	textile-4.0.4
PKGNAME=	${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=	textproc python
MASTER_SITES=	${MASTER_SITE_PYPI:=t/textile/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/textile/python-textile
COMMENT=	XHTML generator using a simple markup
LICENSE=	modified-bsd

TOOL_DEPENDS+=	${PYPKGPREFIX}-setuptools>=78:../../devel/py-setuptools
TOOL_DEPENDS+=	${PYPKGPREFIX}-setuptools_scm-[0-9]*:../../devel/py-setuptools_scm
DEPENDS+=	${PYPKGPREFIX}-nh3-[0-9]*:../../www/py-nh3
DEPENDS+=	${PYPKGPREFIX}-regex>=1.1:../../textproc/py-regex
TEST_DEPENDS+=	${PYPKGPREFIX}-test-cov-[0-9]*:../../devel/py-test-cov

USE_LANGUAGES=	# none

PY_RENAME_BINARIES=	pytextile

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# setuptools gets the version by importing the module, which imports its
# dependencies, which the build machine does not have: give it statically.
SUBST_CLASSES+=		staticver
SUBST_STAGE.staticver=	pre-configure
SUBST_MESSAGE.staticver=	Giving the version statically.
SUBST_FILES.staticver=	pyproject.toml
SUBST_SED.staticver=	-e '/^dynamic = \[ *"version",* *\]$$/s/.*/version = "${PKGVERSION_NOREV}"/'
SUBST_SED.staticver+=	-e '/^version = { *attr = /d'
.endif

.include "../../lang/python/wheel.mk"
.include "../../mk/bsd.pkg.mk"
