# $NetBSD$

DISTNAME=	rust-irix-crates-20261004.2
CATEGORIES=	lang
MASTER_SITES=	# empty: every crate has its own site

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://crates.io/
COMMENT=	Rust crates with IRIX support, for cross-building Rust for IRIX
LICENSE=	mit OR apache-2.0

# The crates, as name-version; each comes from crates.io and is patched in
# patches/ under its own directory.
IRIX_CRATES=	libc-0.2.189
IRIX_CRATES+=	getrandom-0.2.17 getrandom-0.3.4 getrandom-0.4.3
IRIX_CRATES+=	mio-0.8.11 mio-1.2.3
IRIX_CRATES+=	parking_lot_core-0.9.12
IRIX_CRATES+=	socket2-0.4.10 socket2-0.5.10 socket2-0.6.5
IRIX_CRATES+=	libloading-0.7.4 libloading-0.8.9

DISTFILES=	# empty
.for c in ${IRIX_CRATES}
DISTFILES+=		${c}.crate
SITES.${c}.crate=	-${MASTER_SITE_CRATESIO}${c:C/-[0-9][0-9.]*$//}/${c}.crate
.endfor

WRKSRC=		${WRKDIR}
NO_BUILD=	yes
USE_LANGUAGES=	# none

CRATESDIR=	share/rust-irix-crates
INSTALLATION_DIRS=	${CRATESDIR}

do-install:
.for c in ${IRIX_CRATES}
	${CP} -R ${WRKDIR}/${c} ${DESTDIR}${PREFIX}/${CRATESDIR}/${c}
.endfor

GENERATE_PLIST+=	cd ${DESTDIR}${PREFIX} && \
			${FIND} ${CRATESDIR} \( -type f -o -type l \) -print | ${SORT};

.include "../../mk/bsd.pkg.mk"
