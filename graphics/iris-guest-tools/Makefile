# $NetBSD$
#
# The IRIS guest tools (host-GL shims and their tests), from a prebuilt tree.
#
# Built outside pkgsrc by code/iris-guest-tools/clang/build.sh, whose
# "package" stage writes iris-tools-irix65-n32.tgz, laid out for /opt/pkgsrc.
# This package takes that file from IRIS_TOOLS_DIST (a local directory; set
# in mk.conf) and installs it into PREFIX as it is.  As with lang/clang-irix,
# the distfile changes with every build: no distinfo, and "fetching" links
# DISTDIR's copy to the file itself.
#
# Installing does NOT repoint IRIX's GL libraries: that stays an explicit
# step (share/iris-tools/install-iris-gl.sh, see MESSAGE); DEINSTALL warns
# if they still point into the package.

DISTNAME=	iris-tools-irix65-n32
PKGNAME=	iris-guest-tools-${IRIS_TOOLS_VERSION}
CATEGORIES=	graphics
MASTER_SITES=	# none: see do-fetch
EXTRACT_SUFX=	.tgz
DIST_SUBDIR=	iris-guest-tools

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	# none: code/iris-guest-tools, not published
COMMENT=	IRIS emulator guest tools: host-GL shims for IRIX, and tests
# Our own work, under no published license; the IRIS GL stubs are generated
# at build time from SGI's <gl/gl.h>.  Not for redistribution.
LICENSE=	iris-guest-tools-license
RESTRICTED=	Unpublished; built with SGI header-derived stubs.
NO_BIN_ON_CDROM=	${RESTRICTED}
NO_BIN_ON_FTP=		${RESTRICTED}
NO_SRC_ON_CDROM=	${RESTRICTED}
NO_SRC_ON_FTP=		${RESTRICTED}

# The date of the iris-guest-tools commit the tarball was built from
# (git log -1 --format=%cd --date=format:%Y%m%d in code/iris-guest-tools).
IRIS_TOOLS_VERSION?=	20260927
# nb1: GLX colour-index and single-buffered visuals (iris-guest-tools 72dc35b).
PKGREVISION=	1

.include "../../mk/bsd.prefs.mk"

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

do-fetch:
	${RUN}src=${IRIS_TOOLS_DIST:Q}/${DISTFILES:Q};			\
	[ -f "$$src" ] || ${FAIL_MSG} "$$src not found: build it (code/iris-guest-tools/clang/build.sh package) or set IRIS_TOOLS_DIST"; \
	${MKDIR} ${_DISTDIR:Q};						\
	${LN} -sf "$$src" ${_DISTDIR:Q}/${DISTFILES:Q}

# lib/iris-tools/lib32 holds libGL.so (OpenGL) AND libgl.so (IRIS GL): two
# names a case-insensitive build host (a Mac) cannot keep in one directory --
# extracting the tarball there silently leaves only one of them.  So the
# package carries them in two directories, and INSTALL links the lib32
# names to them on IRIX (DEINSTALL removes those links).
do-extract:
	${MKDIR} ${WRKDIR}
	# (the build host's bsdtar, for -s)
	cd ${WRKDIR} && /usr/bin/tar -xzf ${_DISTDIR}/${DISTFILES}		\
	    -s ',/lib32/libGL\.so$$,/opengl/libGL.so,'			\
	    -s ',/lib32/libgl\.so$$,/irisgl/libgl.so,'
	${TEST} -f ${WRKSRC}/lib/iris-tools/opengl/libGL.so
	${TEST} -f ${WRKSRC}/lib/iris-tools/irisgl/libgl.so
	rmdir ${WRKSRC}/lib/iris-tools/lib32

do-install:
	cd ${WRKSRC} && ${PAX} -rw -pp . ${DESTDIR}${PREFIX}

.include "../../mk/bsd.pkg.mk"
