# $NetBSD$

DISTNAME=	HolliDanceSGI_1_6
PKGNAME=	hollidance-1.6
CATEGORIES=	benchmarks graphics
MASTER_SITES=	http://www.cool3dworld.org/HolliDance/
DIST_SUBDIR=	hollidance

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.cool3dworld.org/HolliDanceSGI.html
COMMENT=	Holli Dance, a 3D dancer in a night club (IRIX binary)
LICENSE=	hollidance-license

RESTRICTED=		No commercial distribution
NO_BIN_ON_CDROM=	${RESTRICTED}
NO_SRC_ON_CDROM=	${RESTRICTED}

# The author's IRIX binary (n32, mips3: OpenGL, Motif, audio); no sources.
ONLY_FOR_PLATFORM=	IRIX-*-*
WRKSRC=			${WRKDIR}/HolliDance
USE_TOOLS+=		pax
NO_CONFIGURE=		yes
NO_BUILD=		yes
CHECK_SHLIBS_SUPPORTED=	no
CHECK_RELRO_SUPPORTED=	no
CHECK_SSP_SUPPORTED=	no
CHECK_PIE_SUPPORTED=	no
# Installed as the author made them: no stripping.
STRIP_DEBUG_SUPPORTED=	no

INSTALLATION_DIRS=	bin lib/hollidance

# The terms ask for all of the files, so the whole tree is installed,
# unstripped; bin/hollidance runs it from a directory of your own.
do-install:
	cd ${WRKSRC} && ${PAX} -rw . ${DESTDIR}${PREFIX}/lib/hollidance
	${CHMOD} -R u+rwX,go+rX,go-w ${DESTDIR}${PREFIX}/lib/hollidance
	${SED} -e 's,@PREFIX@,${PREFIX},g' ${FILESDIR}/hollidance.sh \
	    > ${DESTDIR}${PREFIX}/bin/hollidance
	${CHMOD} 755 ${DESTDIR}${PREFIX}/bin/hollidance

.include "../../mk/bsd.pkg.mk"
