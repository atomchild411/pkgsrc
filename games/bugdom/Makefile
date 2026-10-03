# $NetBSD: Makefile,v 1.8 2026/09/02 19:02:06 wiz Exp $

DISTNAME=	bugdom-1.3.4
PKGREVISION=	3
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=jorio/}

MAINTAINER=	charlotte@NetBSD.org
HOMEPAGE=	https://pangeasoft.net/bug/
COMMENT=	Pangea Software's Bugdom for modern systems
LICENSE=	cc-by-nc-sa-v4.0-license

GITHUB_SUBMODULES=	\
	jorio Pomme ef94150e2dcec522e3099f4d03a4e8f2639f7232 extern/Pomme

WRKSRC=		${WRKDIR}/Bugdom-${PKGVERSION_NOREV}

USE_LANGUAGES=	c c++
USE_TOOLS+=	pax pkg-config

INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	libexec
INSTALLATION_DIRS+=	share/bugdom/Data

pre-configure:
	${SED} -e 's,@@PREFIX@@,${PREFIX},g' \
		${FILESDIR}/bugdom.template > ${WRKDIR}/bugdom

do-install:
	${INSTALL_SCRIPT} ${WRKDIR}/bugdom ${DESTDIR}${PREFIX}/bin/bugdom
	${INSTALL_PROGRAM} ${WRKSRC}/${CMAKE_BUILD_DIR}/Bugdom ${DESTDIR}${PREFIX}/libexec
	(cd ${WRKSRC}/Data && ${PAX} -r -w . ${DESTDIR}${PREFIX}/share/bugdom/Data)

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
