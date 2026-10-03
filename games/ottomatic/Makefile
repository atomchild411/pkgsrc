# $NetBSD: Makefile,v 1.12 2026/09/02 19:02:20 wiz Exp $

DISTNAME=	ottomatic-4.0.1
PKGREVISION=	9
CATEGORIES=	games
MASTER_SITES=	${MASTER_SITE_GITHUB:=jorio/}

MAINTAINER=	charlotte@NetBSD.org
HOMEPAGE=	https://pangeasoft.net/otto/
COMMENT=	Pangea Software's Otto Matic
LICENSE=	cc-by-nc-sa-v4.0-license

GITHUB_SUBMODULES=	\
	jorio Pomme ad9cc177d2187f67bd00cb6cf2b3045ef91c577b extern/Pomme

USE_LANGUAGES=	c c++
USE_TOOLS+=	pax pkg-config

USE_CXX_FEATURES+=	has_include

WRKSRC=			${WRKDIR}/OttoMatic-${PKGVERSION_NOREV}

INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	libexec
INSTALLATION_DIRS+=	share/ottomatic/Data

pre-configure:
	${SED} -e 's,@@PREFIX@@,${PREFIX},g' \
		${FILESDIR}/ottomatic.template > ${WRKDIR}/ottomatic

do-install:
	${INSTALL_SCRIPT} ${WRKDIR}/ottomatic ${DESTDIR}${PREFIX}/bin/ottomatic
	${INSTALL_PROGRAM} ${WRKSRC}/${CMAKE_BUILD_DIR}/OttoMatic ${DESTDIR}${PREFIX}/libexec
	(cd ${WRKSRC}/Data && ${PAX} -r -w . ${DESTDIR}${PREFIX}/share/ottomatic/Data)

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
