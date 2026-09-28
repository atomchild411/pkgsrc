# $NetBSD$
#
# xephyr-app and fillwm, from a prebuilt tree.
#
# Built outside pkgsrc by code/iris-guest-tools/clang/build.sh xapp, whose
# dist/xephyr-app-irix65-n32.tgz (rooted at /: opt/pkgsrc/bin/fillwm and
# xephyr-app) is the distfile; nothing is compiled here. fillwm links with
# IRIX's own libX11.

DISTNAME=	xephyr-app-irix65-n32
PKGNAME=	xephyr-app-${XEPHYR_APP_VERSION}
CATEGORIES=	x11
MASTER_SITES=	# none: see do-fetch
EXTRACT_SUFX=	.tgz
DIST_SUBDIR=	iris-guest-tools

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	# none: code/iris-guest-tools, not published
COMMENT=	Run newer X programs on IRIX, each in its own Xephyr window
LICENSE=	iris-guest-tools-license

XEPHYR_APP_VERSION?=	20260927

.include "../../mk/bsd.prefs.mk"

# The same directory as graphics/iris-guest-tools' archive.
IRIS_TOOLS_DIST?=	/nonexistent/set-IRIS_TOOLS_DIST-in-mk.conf

ONLY_FOR_PLATFORM=	IRIX-*-*
NO_CHECKSUM=		yes
NO_CONFIGURE=		yes
NO_BUILD=		yes
USE_LANGUAGES=		# none: nothing is compiled
USE_TOOLS+=		pax
STRIP_DEBUG_SUPPORTED=	no
CHECK_SHLIBS_SUPPORTED=	no
WRKSRC=		${WRKDIR}/opt/pkgsrc

DEPENDS+=	modular-xorg-xephyr>=21.1.24nb2:../../x11/modular-xorg-xephyr
DEPENDS+=	xkbcomp-[0-9]*:../../x11/xkbcomp
DEPENDS+=	xkeyboard-config-[0-9]*:../../x11/xkeyboard-config

do-fetch:
	${RUN}src=${IRIS_TOOLS_DIST:Q}/${DISTFILES:Q};			\
	[ -f "$$src" ] || ${FAIL_MSG} "$$src not found: build it (code/iris-guest-tools/clang/build.sh xapp) or set IRIS_TOOLS_DIST"; \
	${MKDIR} ${_DISTDIR:Q};						\
	${LN} -sf "$$src" ${_DISTDIR:Q}/${DISTFILES:Q}

do-extract:
	${MKDIR} ${WRKDIR}
	cd ${WRKDIR} && /usr/bin/tar -xzf ${_DISTDIR}/${DISTFILES}
	${TEST} -f ${WRKSRC}/bin/fillwm
	${TEST} -f ${WRKSRC}/bin/xephyr-app

do-install:
	cd ${WRKSRC} && ${PAX} -rw -pp . ${DESTDIR}${PREFIX}

.include "../../mk/bsd.pkg.mk"
