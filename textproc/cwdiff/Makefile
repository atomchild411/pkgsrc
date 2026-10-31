# $NetBSD: Makefile,v 1.6 2019/11/04 21:43:34 rillig Exp $

VERSION=	0.4.0
DISTNAME=	cwdiff-${VERSION}
PKGREVISION=	1
CATEGORIES=	textproc
MASTER_SITES=	${MASTER_SITE_GITHUB:=junghans/}
GITHUB_TAG=	v${VERSION}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/junghans/cwdiff
COMMENT=	Color wrapper for wdiff (word diff)
LICENSE=	gnu-gpl-v2

USE_TOOLS+=	bash
USE_TOOLS+=		bash:run	# scripts run with bash (see install-irix-bash)
NO_BUILD=	yes
REPLACE_BASH=	cwdiff

INSTALLATION_DIRS+=	share/examples/cwdiff/
AUTO_MKDIRS=		yes

do-install:
	(cd ${WRKSRC} ;\
	${INSTALL_SCRIPT} cwdiff          ${DESTDIR}${PREFIX}/bin ;\
	${INSTALL_DATA} cwdiff.rc  ${DESTDIR}${PREFIX}/${INSTALLATION_DIRS} ;\
	)

.include "../../mk/bsd.pkg.mk"
