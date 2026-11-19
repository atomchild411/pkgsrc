# $NetBSD$

DISTNAME=	HolliDance
PKGNAME=	hollidance-classic-1998
CATEGORIES=	benchmarks graphics
MASTER_SITES=	http://www.sgidepot.co.uk/depot/
DIST_SUBDIR=	hollidance

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.sgidepot.co.uk/hollibench.html
COMMENT=	Holli Dance 1998, the version of the SGI benchmark table
LICENSE=	hollidance-license

RESTRICTED=		No commercial distribution
NO_BIN_ON_CDROM=	${RESTRICTED}
NO_SRC_ON_CDROM=	${RESTRICTED}

# The author's IRIX binaries (n32, and o32 for IRIX 5.3); no sources.
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

INSTALLATION_DIRS=	bin lib/hollidance-classic

# All of the files (the terms ask for them), unstripped. The archive's
# files are not readable by others: install them readable.
do-install:
	cd ${WRKSRC} && ${PAX} -rw . ${DESTDIR}${PREFIX}/lib/hollidance-classic
	${CHMOD} -R u+rwX,go+rX,go-w ${DESTDIR}${PREFIX}/lib/hollidance-classic
	${SED} -e 's,@PREFIX@,${PREFIX},g' ${FILESDIR}/hollidance-1998.sh \
	    > ${DESTDIR}${PREFIX}/bin/hollidance-1998
	${CHMOD} 755 ${DESTDIR}${PREFIX}/bin/hollidance-1998

.include "../../mk/bsd.pkg.mk"
