# $NetBSD: Makefile,v 1.70 2026/04/18 10:25:07 fox Exp $

DISTNAME=	psutil-7.2.2
PKGNAME=	${PYPKGPREFIX}-${DISTNAME}
PKGREVISION=    4
CATEGORIES=	sysutils python
MASTER_SITES=	${MASTER_SITE_PYPI:=p/psutil/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/giampaolo/psutil
COMMENT=	Cross-platform process and system utilities module for Python
LICENSE=	modified-bsd

TOOL_DEPENDS+=	${PYPKGPREFIX}-setuptools>=78:../../devel/py-setuptools
TEST_DEPENDS+=	${PYPKGPREFIX}-psleak>0:../../sysutils/py-psleak
TEST_DEPENDS+=	${PYPKGPREFIX}-test-instafail>0:../../devel/py-test-instafail
TEST_DEPENDS+=	${PYPKGPREFIX}-test-xdist>0:../../devel/py-test-xdist

USE_TOOLS+=	gmake

.include "../../mk/bsd.prefs.mk"

# IRIX: the platform module (procfs, sysmp, swapctl, utmpx).
.if ${OPSYS} == "IRIX"
post-extract:
	${CP} ${FILESDIR}/_psirix.py ${FILESDIR}/_psutil_irix.c ${WRKSRC}/psutil/
	${MKDIR} ${WRKSRC}/psutil/arch/irix
	${CP} ${FILESDIR}/arch-irix/sysinfo.c ${FILESDIR}/arch-irix/sysinfo.h \
		${WRKSRC}/psutil/arch/irix/
.endif

# as of 7.2.1
# 3 failed, 303 passed, 285 skipped
do-test:
	cd ${WRKSRC} && ${SETENV} ${TEST_ENV} ${GMAKE} build test

.include "../../lang/python/wheel.mk"
.include "../../lang/python/tool.mk"
.include "../../mk/bsd.pkg.mk"
