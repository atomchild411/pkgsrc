# $NetBSD$

DISTNAME=	libc-0.2.189
PKGNAME=	rust-irix-crates-0.2.189
CATEGORIES=	lang
MASTER_SITES=	${MASTER_SITE_CRATESIO}libc/
EXTRACT_SUFX=	.crate

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/rust-lang/libc
COMMENT=	Rust crates with IRIX support, for cross-building Rust for IRIX
LICENSE=	mit OR apache-2.0

NO_BUILD=	yes
USE_LANGUAGES=	# none

CRATESDIR=	share/rust-irix-crates
INSTALLATION_DIRS=	${CRATESDIR}/libc

do-install:
	${CP} -R ${WRKSRC}/. ${DESTDIR}${PREFIX}/${CRATESDIR}/libc

GENERATE_PLIST+=	cd ${DESTDIR}${PREFIX} && \
			${FIND} ${CRATESDIR} \( -type f -o -type l \) -print | ${SORT};

.include "../../mk/bsd.pkg.mk"
