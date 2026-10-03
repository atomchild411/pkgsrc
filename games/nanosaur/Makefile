# $NetBSD: Makefile,v 1.12 2026/09/02 19:02:19 wiz Exp $

DISTNAME=	nanosaur-1.4.4
PKGREVISION=	9
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=jorio/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	charlotte@NetBSD.org
HOMEPAGE=	https://www.pangeasoft.net/nano/index.html
COMMENT=	Source port of Nanosaur from Pangea Software
LICENSE=	cc-by-nc-sa-v4.0-license

GITHUB_SUBMODULES=	\
	jorio Pomme fd1cd2cf81a2d39a4e47e76485860a87f0bf33f6 extern/Pomme

WRKSRC=		${WRKDIR}/Nanosaur-${PKGVERSION_NOREV}

USE_LANGUAGES=	c c++
USE_TOOLS+=	pax pkg-config

USE_CXX_FEATURES+=	has_include

INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	libexec
INSTALLATION_DIRS+=	share/nanosaur/Data

pre-configure:
	${SED} -e 's,@@PREFIX@@,${PREFIX},g' \
		${FILESDIR}/nanosaur.template > ${WRKDIR}/nanosaur

do-install:
	${INSTALL_SCRIPT} ${WRKDIR}/nanosaur ${DESTDIR}${PREFIX}/bin/nanosaur
	${INSTALL_PROGRAM} ${WRKSRC}/${CMAKE_BUILD_DIR}/Nanosaur ${DESTDIR}${PREFIX}/libexec
	(cd ${WRKSRC}/Data && ${PAX} -r -w . ${DESTDIR}${PREFIX}/share/nanosaur/Data)

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
