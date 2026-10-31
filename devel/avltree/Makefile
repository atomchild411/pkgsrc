# $NetBSD: Makefile,v 1.17 2022/03/03 09:36:09 jperkin Exp $

DISTNAME=	avltree-1.1
PKGREVISION=	3
CATEGORIES=	devel
MASTER_SITES=	# ftp://odin.compchem.ucsf.edu/pub/amber/

MAINTAINER=	pkgsrc-users@NetBSD.org
COMMENT=	In-memory index w/ binary and string keys and key counts

USE_TOOLS+=	nroff

MANCOMPRESSED_IF_MANZ=	yes
INSTALL_TARGET=		includes install
USE_BSD_MAKEFILE=	yes
MAKE_FLAGS+=		MKPROFILE=yes

INSTALLATION_DIRS=	include lib ${PKGMANDIR}/cat3 ${PKGMANDIR}/man3

post-extract:
	cp -f ${FILESDIR}/Makefile ${WRKSRC}/

.include "../../mk/bsd.prefs.mk"

# IRIX: bsd.lib.mk links shared libraries with ld -nostdlib; add the compiler
# runtime, which holds the libc add-ons (__irix_*) that the objects call.
.if ${OPSYS} == "IRIX"
MAKE_FLAGS+=	SHLIB_LDENDFILE="$$(${CC} -print-libgcc-file-name)"
.endif

.if ${OPSYS} == "Darwin"
post-install:
	${RUN} install_name_tool -id ${PREFIX}/lib/libavltree.so.1.1 \
	    ${DESTDIR}${PREFIX}/lib/libavltree.so.1.1
.endif

.include "../../mk/bsd.pkg.mk"
