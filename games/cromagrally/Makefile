# $NetBSD: Makefile,v 1.13 2026/09/02 19:02:08 wiz Exp $

DISTNAME=	cromagrally-3.0.1
PKGREVISION=	6
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=jorio/}

MAINTAINER=	charlotte@NetBSD.org
HOMEPAGE=	https://pangeasoft.net/cromag/
COMMENT=	Source port of Cro-Mag Rally from Pangea Software
LICENSE=	cc-by-nc-sa-v4.0-license

GITHUB_SUBMODULES=	\
	jorio Pomme ef94150e2dcec522e3099f4d03a4e8f2639f7232 extern/Pomme

USE_LANGUAGES=		c c++
FORCE_CXX_STD=		c++20
USE_CXX_FEATURES=	c++20
USE_TOOLS+=		pax pkg-config

WRKSRC=		${WRKDIR}/CroMagRally-${GITHUB_TAG}

INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	libexec
INSTALLATION_DIRS+=	share/cromagrally/Data

pre-configure:
	${SED} -e 's,@@PREFIX@@,${PREFIX},g' \
		${FILESDIR}/cromagrally.template > ${WRKDIR}/cromagrally

do-install:
	${INSTALL_SCRIPT} ${WRKDIR}/cromagrally ${DESTDIR}${PREFIX}/bin/cromagrally
	${INSTALL_PROGRAM} ${WRKSRC}/${CMAKE_BUILD_DIR}/CroMagRally ${DESTDIR}${PREFIX}/libexec
	(cd ${WRKSRC}/Data && ${PAX} -r -w . ${DESTDIR}${PREFIX}/share/cromagrally/Data)

.include "../../devel/cmake/build.mk"
.include "../../devel/SDL2/buildlink3.mk"
# Pomme keeps GCC before 9 off <filesystem> by testing __GNUC__, which
# clang sets to 4: clang got the bundled ghc::filesystem instead, which
# knows no IRIX ("Operating system currently not supported!").
SUBST_CLASSES+=		pommefs
SUBST_STAGE.pommefs=	pre-configure
SUBST_MESSAGE.pommefs=	Letting clang use <filesystem>.
SUBST_FILES.pommefs=	extern/Pomme/src/CompilerSupport/filesystem.h
SUBST_SED.pommefs=	-e 's/defined(__GNUC__) && __GNUC__ < 9/defined(__GNUC__) \&\& !defined(__clang__) \&\& __GNUC__ < 9/'

.include "../../mk/bsd.pkg.mk"
