# $NetBSD: Makefile,v 1.19 2026/08/30 15:29:41 wiz Exp $

DISTNAME=	kiwisolver-1.5.1
PKGNAME=	${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=	math python
MASTER_SITES=	${MASTER_SITE_PYPI:=k/kiwisolver/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/nucleic/kiwi
COMMENT=	Fast implementation of the Cassowary constraint solver
LICENSE=	modified-bsd

TOOL_DEPENDS+=	${PYPKGPREFIX}-setuptools>=78:../../devel/py-setuptools
TOOL_DEPENDS+=	${PYPKGPREFIX}-setuptools_scm>=3.4.3:../../devel/py-setuptools_scm

USE_LANGUAGES=	c c++

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# setup.py imports cppy (for its headers' location) with the build
# machine's python, which names the build machine's copy: use the
# target's (the same headers) instead.
TOOL_DEPENDS+=	${PYPKGPREFIX}-cppy>=1.3.0:../../devel/py-cppy
CPPFLAGS+=	-I${BUILDLINK_DIR}/${PYSITELIB}/cppy/include
.endif

post-install:
	${RM} -f ${DESTDIR}${PREFIX}/${PYSITELIB}/src/version.h
	${RMDIR} ${DESTDIR}${PREFIX}/${PYSITELIB}/src || ${TRUE}

BUILDLINK_API_DEPENDS.py-cppy+=	${PYPKGPREFIX}-cppy>=1.3.0
.include "../../devel/py-cppy/buildlink3.mk"
.include "../../lang/python/wheel.mk"
.include "../../mk/bsd.pkg.mk"
