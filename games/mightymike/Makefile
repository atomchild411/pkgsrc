# $NetBSD: Makefile,v 1.10 2026/09/02 19:02:18 wiz Exp $

DISTNAME=	mightymike-3.0.2
PKGREVISION=	7
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=jorio/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	charlotte@NetBSD.org
HOMEPAGE=	https://jorio.itch.io/mightymike
COMMENT=	Pangea Software's Mighty Mike (Power Pete) for modern systems
LICENSE=	cc-by-nc-sa-v4.0-license

GITHUB_SUBMODULES=	\
	jorio Pomme d57c28e205462e51063e787f9ebddaadff592f1e extern/Pomme

WRKSRC=	${WRKDIR}/MightyMike-${PKGVERSION_NOREV}

USE_LANGUAGES=	c c++
USE_TOOLS+=	pax pkg-config

USE_CXX_FEATURES+=	has_include

INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	libexec
INSTALLATION_DIRS+=	share/mightymike/Data

pre-configure:
	${SED} -e 's,@@PREFIX@@,${PREFIX},g' \
		${FILESDIR}/mightymike.template > ${WRKDIR}/mightymike

do-install:
	${INSTALL_SCRIPT} ${WRKDIR}/mightymike ${DESTDIR}${PREFIX}/bin/mightymike
	${INSTALL_PROGRAM} ${WRKSRC}/${CMAKE_BUILD_DIR}/MightyMike ${DESTDIR}${PREFIX}/libexec
	(cd ${WRKSRC}/Data && ${PAX} -r -w . ${DESTDIR}${PREFIX}/share/mightymike/Data)

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
