# $NetBSD: Makefile,v 1.28 2025/10/31 08:35:03 adam Exp $

DISTNAME=	django_extensions-4.1
PKGNAME=	${PYPKGPREFIX}-${DISTNAME:S/_/-/}
CATEGORIES=	www python
MASTER_SITES=	${MASTER_SITE_PYPI:=d/django-extensions/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/django-extensions/django-extensions
COMMENT=	Extensions for Django
LICENSE=	mit

TOOL_DEPENDS+=	${PYPKGPREFIX}-setuptools>=78:../../devel/py-setuptools
DEPENDS+=	${PYPKGPREFIX}-django>=4.2:../../www/py-django

USE_LANGUAGES=	# none

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
