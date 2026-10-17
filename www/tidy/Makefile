# $NetBSD: Makefile,v 1.60 2025/08/11 08:40:39 wiz Exp $

DISTNAME=	tidy-html5-5.8.0
PKGNAME=	${DISTNAME:S/-html5//}
CATEGORIES=	www textproc
MASTER_SITES=	${MASTER_SITE_GITHUB:=htacg/}
GITHUB_PROJECT=	tidy-html5

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.html-tidy.org/
COMMENT=	Fixes and tidies up HTML files
LICENSE=	mit

# for man page
TOOL_DEPENDS+=	libxslt-[0-9]*:../../textproc/libxslt

USE_LANGUAGES=		c c++
PKGCONFIG_OVERRIDE=	tidy.pc.cmake.in

GCC_REQD+=	4.4

CMAKE_CONFIGURE_ARGS+=	-DMAN_INSTALL_DIR:PATH=${PKGMANDIR}/man1
CMAKE_CONFIGURE_ARGS+=	-DINCLUDE_INSTALL_DIR:PATH=include/tidy
CMAKE_CONFIGURE_ARGS+=	-DCMAKE_POLICY_VERSION_MINIMUM=3.5

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == yes
# The man page comes from "tidy -xml-help" and "-xml-config": run the build
# machine's tidy.
TOOL_DEPENDS+=		tidy-[0-9]*:../../www/tidy
SUBST_CLASSES+=		host-tidy
SUBST_STAGE.host-tidy=	pre-configure
SUBST_MESSAGE.host-tidy=	Generating the man page with the build machine's tidy.
SUBST_FILES.host-tidy=	CMakeLists.txt
SUBST_SED.host-tidy=	-e 's|COMMAND $${CMAKE_CURRENT_BINARY_DIR}/$${LIB_NAME} -xml-|COMMAND ${TOOLBASE}/bin/tidy -xml-|'
.endif

.include "../../devel/cmake/build.mk"
.include "../../mk/bsd.pkg.mk"
