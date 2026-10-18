# $NetBSD: Makefile,v 1.2 2022/09/11 11:58:20 martin Exp $

DISTNAME=	sunwait-0.8
PKGREVISION=	1
CATEGORIES=	misc
MASTER_SITES=	${MASTER_SITE_GITHUB:=klada/}

MAINTAINER=	martin@NetBSD.org
HOMEPAGE=	https://github.com/klada/sunwait
COMMENT=	Calculate sunrise, sunset and twilight
LICENSE=	gnu-gpl-v2

USE_LANGUAGES+=	c++11

# patch-Makefile passes -D__linux__ to mean "POSIX"; with libc++ that also
# selects its Linux locale support (strtof_l and friends), which IRIX lacks.
# Use a macro of the package's own.
SUBST_CLASSES.IRIX+=	posix
SUBST_STAGE.posix=	post-patch
SUBST_FILES.posix=	Makefile sunwait.cpp
SUBST_SED.posix=	-e 's,__linux__,SUNWAIT_POSIX,g'

.include "../../mk/bsd.pkg.mk"
