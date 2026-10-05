# $NetBSD$

DISTNAME=	netscape-5.0beta1
PKGNAME=	netscape5-5.0beta1
CATEGORIES=	www
MASTER_SITES=	${MASTER_SITE_GITHUB:=atomchild411/}
GITHUB_PROJECT=	netscape
# Branch irix of the fork: the 1998 tree (github.com/zii/netscape) ported to
# IRIX with today's compilers, with TLS from OpenSSL.
GITHUB_TAG=	618237fca22597936c67daeb90f87f616db4a50a

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/atomchild411/netscape
COMMENT=	Netscape Navigator 5.0 beta (1998 Mozilla Classic), browser only
LICENSE=	npl-1.0

WRKSRC=		${WRKDIR}/${GITHUB_PROJECT}-${GITHUB_TAG}

USE_LANGUAGES=	c c++
USE_TOOLS+=	gmake perl
NO_CONFIGURE=	yes
INSTALLATION_DIRS=	bin
# Recursive 1998 makefiles: each directory exports, then builds, in order.
MAKE_JOBS_SAFE=	no

# The Navigator-only configuration (config/config.mk: MOZ_LITE).
MAKE_FLAGS+=	MOZILLA_CLIENT=1 MOZ_LITE=1 BUILD_OPT=1 NO_MDUPDATE=1
MAKE_FLAGS+=	NS_USE_GCC=1 NO_SECURITY=1 USE_PTHREADS=1 USE_N32=1
# TLS from OpenSSL (network/main/mktls.c), trusting pkgsrc's Mozilla roots.
MAKE_FLAGS+=	NS_OPENSSL=1
# X class Netscape5 and profile ~/.netscape5: Netscape 4 (IRIX ships 4.8)
# owns app-defaults/Netscape and ~/.netscape.
MAKE_FLAGS+=	NS_PROGCLASS=Netscape5 NS_PROFILE_DIR=.netscape5
DEPENDS+=	mozilla-rootcerts-openssl-[0-9]*:../../security/mozilla-rootcerts-openssl
# C and C++ in their 1998 dialects: implicit int and implicit declarations
# are errors from C99 on, and C++17 has no "register".  The C++ runtime is
# linked in: the browser is one program, with no libc++ to match on IRIX.
MAKE_FLAGS+=	CC=${CC:Q}\ -std=gnu89
MAKE_FLAGS+=	CCC=${CXX:Q}\ -std=gnu++98\ -static-libstdc++
MAKE_FLAGS+=	HOST_CC=${NATIVE_CC:Q}
# Only the statically linked program (mozilla-export): the shared variant
# would link the tree's own libpng 0.95 as -lpng, which buildlink turns into
# pkgsrc's libpng16.
MAKE_FLAGS+=	NO_NETSCAPE_SHARED=1

.include "../../mk/bsd.prefs.mk"

# Development: build a live source tree instead of the distfile
# (NETSCAPE_DEVSRC=/path/to/netscape), keeping its objects between builds.
.if !empty(NETSCAPE_DEVSRC)
DISTFILES=	# none
NO_CHECKSUM=	yes
WRKSRC=		${WRKDIR}/netscape-dev
MAKE_FLAGS+=	-k EXIT_ON_ERROR=+e
do-extract:
	${MKDIR} ${WRKDIR}
	${LN} -s ${NETSCAPE_DEVSRC} ${WRKSRC}
.endif

.include "options.mk"

.include "../../security/openssl/buildlink3.mk"

# The tree's own install target only fills its dist/ directory.  The browser
# is one program (resources compiled in); its object directory is named for
# the target (IRIX6.5_OPT.OBJ).  Installed as netscape5: www/netscape owns
# bin/netscape (a launcher for whichever browser is installed).
do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/cmd/xfe/*_OPT.OBJ/mozilla-export \
	    ${DESTDIR}${PREFIX}/bin/netscape5

.include "../../mk/bsd.pkg.mk"
