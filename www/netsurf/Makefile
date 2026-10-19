# $NetBSD: Makefile,v 1.134 2026/09/02 19:05:00 wiz Exp $

DISTNAME=	netsurf-all-3.11
PKGNAME=	${DISTNAME:S/-all//}
PKGREVISION=	40
CATEGORIES=	www
MASTER_SITES=	https://download.netsurf-browser.org/netsurf/releases/source-full/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.netsurf-browser.org/
COMMENT=	Web browser for RISC OS and UNIX-like platforms
LICENSE=	gnu-gpl-v2 AND mit

TOOL_DEPENDS+=	lemon>=1.0:../../devel/lemon
TOOL_DEPENDS+=	re2c>=0.12:../../devel/re2c
TOOL_DEPENDS+=	p5-HTML-Parser-[0-9]*:../../www/p5-HTML-Parser
# Needed for the xxd utility
TOOL_DEPENDS+=	vim-share-[0-9]*:../../editors/vim-share

BUILD_TARGET=	build
USE_TOOLS+=	bison flex gmake perl:build pax pkg-config

MAKE_FLAGS+=	TARGET=gtk3

# gmake[1]: *** No rule to make target 'build-x86_64--netbsd-x86_64--netbsd-release-lib-static/filter-lexer.inc', needed by 'build-x86_64--netbsd-x86_64--netbsd-release-lib-static/filter-lexer.c'.  Stop.
# src/filter-parser.y:15:10: fatal error: filter-lexer.h: No such file or directory
MAKE_JOBS_SAFE=	no

SUBST_CLASSES+=			ssl-certs
SUBST_STAGE.ssl-certs=		pre-configure
SUBST_MESSAGE.ssl-certs=	Fixing hardcoded paths for SSL certs
SUBST_FILES.ssl-certs=		netsurf/frontends/beos/gui.cpp
SUBST_FILES.ssl-certs+=		netsurf/test/data/Choices
SUBST_FILES.ssl-certs+=		netsurf/test/data/Choices-all
SUBST_FILES.ssl-certs+=		netsurf/test/data/Choices-full
SUBST_FILES.ssl-certs+=		netsurf/test/data/Choices-short
SUBST_SED.ssl-certs=		-e 's,/etc/ssl/certs,${SSLCERTS},'

# Avoid possible problems with already often defined HOST
MAKE_ENV+=	BUILD="${MACHINE_GNU_ARCH}--${LOWER_OPSYS}"
MAKE_ENV+=	HOST="${MACHINE_GNU_ARCH}--${LOWER_OPSYS}"
.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# The buildsystem compiles its generators (libcss's gen_parser, ...) with
# BUILD_CC, "cc" by default: the target's here. The build tools it
# installs first (nsgenbind) are made with CC: give them BUILD_CC, and
# none of the target's CFLAGS and LDFLAGS.
MAKE_FLAGS+=	BUILD_CC=${NATIVE_CC:Q}	# netsurf/Makefile sets it with :=
# netsurf's own tools (split-messages, convert_image) use zlib and libpng:
# the build machine's.
NETSURF_BUILD_LDFLAGS=	-L${TOOLBASE}/lib -Wl,-rpath,${TOOLBASE}/lib
MAKE_FLAGS+=	BUILD_CFLAGS=-I${TOOLBASE}/include
MAKE_FLAGS+=	BUILD_LDFLAGS=${NETSURF_BUILD_LDFLAGS:Q}
SUBST_CLASSES+=		buildtool
SUBST_STAGE.buildtool=	pre-build
SUBST_FILES.buildtool=	Makefile
SUBST_SED.buildtool=	-e 's,$$(MAKE) install --directory=$$1 HOST=$$(BUILD) PREFIX,CFLAGS=-O2 LDFLAGS= $$(MAKE) install --directory=$$1 HOST=$$(BUILD) CC=$$(BUILD_CC) PREFIX,'
SUBST_MESSAGE.buildtool=	Building nsgenbind for the build host.
.endif

INSTALLATION_DIRS+=	bin
INSTALLATION_DIRS+=	share/applications
INSTALLATION_DIRS+=	share/netsurf
INSTALLATION_DIRS+=	share/pixmaps

BUILDLINK_TRANSFORM+=	rm:-Werror
CFLAGS.NetBSD+=		-D_NETBSD_SOURCE	# needed for strcasestr(3) and strndup(3)

SUBST_CLASSES+=		tools
SUBST_STAGE.tools=	pre-build
SUBST_MESSAGE.tools=	Remove the -C option
SUBST_FILES.tools=	buildsystem/makefiles/Makefile.tools
SUBST_SED.tools=	-e 's,install -C,install,'

SUBST_CLASSES+=		bin
SUBST_STAGE.bin=	pre-install
SUBST_MESSAGE.bin=	Changing executable name in .desktop file
SUBST_FILES.bin=	netsurf/frontends/gtk/res/netsurf-gtk.desktop
SUBST_SED.bin=		-e 's,netsurf-gtk,netsurf-gtk3,g'

post-install:
	${INSTALL_DATA} ${WRKSRC}/netsurf/frontends/gtk/res/netsurf.xpm \
		${DESTDIR}${PREFIX}/share/pixmaps/netsurf.xpm
	${INSTALL_DATA} ${WRKSRC}/netsurf/frontends/gtk/res/netsurf-gtk.desktop \
		${DESTDIR}${PREFIX}/share/applications/netsurf-gtk.desktop

.include "../../converters/libiconv/buildlink3.mk"
.include "../../devel/gperf/buildlink3.mk"
.include "../../devel/pango/buildlink3.mk"
.include "../../graphics/adwaita-icon-theme/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../textproc/expat/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../x11/gtk3/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
