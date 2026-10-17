# $NetBSD: Makefile,v 1.11 2026/01/02 12:17:14 triaxx Exp $

DISTNAME=	mp4v2-5.0.1
PKGREVISION=	1
CATEGORIES=	multimedia
MASTER_SITES=	${MASTER_SITE_GITHUB:=TechSmith/}
GITHUB_TAG=	Release-ThirdParty-MP4v2-${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/TechSmith/mp4v2
COMMENT=	Library for reading and modifying mp4 files
LICENSE=	mpl-1.1

WRKSRC=		${WRKDIR}/mp4v2-${GITHUB_TAG}

USE_LANGUAGES=		c c++
USE_CXX_FEATURES=	c++11
USE_LIBTOOL=		yes
USE_PKGLOCALEDIR=	yes
USE_TOOLS+=		gmake
GNU_CONFIGURE=		yes
MAKE_FILE=		GNUmakefile

.include "../../mk/bsd.prefs.mk"

.if ${USE_CROSS_COMPILE:tl} == "yes"
# help2man would run the utilities just built. Without it the man pages are
# installed empty, as they are natively where help2man is not installed.
CONFIGURE_ENV+=		ac_cv_prog_FOUND_HELP2MAN=no
.endif

.include "../../mk/bsd.pkg.mk"
