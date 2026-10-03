# $NetBSD: Makefile,v 1.9 2026/09/02 19:02:06 wiz Exp $

DISTNAME=	bugdom2-4.0.0
PKGREVISION=	6
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=jorio/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	charlotte@NetBSD.org
HOMEPAGE=	https://jorio.itch.io/bugdom2
COMMENT=	Source port of Bugdom 2 from Pangea Software
LICENSE=	cc-by-nc-sa-v4.0-license

GITHUB_SUBMODULES=	\
	jorio Pomme c6a38eab19a11847024a13f9b3e2af0c2d908c3e extern/Pomme

USE_LANGUAGES=		c c++
FORCE_CXX_STD=		c++20
USE_CXX_FEATURES=	c++20
USE_TOOLS+=		pax pkg-config

WRKSRC=		${WRKDIR}/Bugdom2-${PKGVERSION_NOREV}

INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	libexec
INSTALLATION_DIRS+=	share/bugdom2/Data

pre-configure:
	${SED} -e 's,@@PREFIX@@,${PREFIX},g' \
		${FILESDIR}/bugdom2.template > ${WRKDIR}/bugdom2

do-install:
	${INSTALL_SCRIPT} ${WRKDIR}/bugdom2 ${DESTDIR}${PREFIX}/bin/bugdom2
	${INSTALL_PROGRAM} ${WRKSRC}/${CMAKE_BUILD_DIR}/Bugdom2 ${DESTDIR}${PREFIX}/libexec
	(cd ${WRKSRC}/Data && ${PAX} -r -w . ${DESTDIR}${PREFIX}/share/bugdom2/Data)

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
