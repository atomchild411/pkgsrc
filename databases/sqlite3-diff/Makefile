# $NetBSD: Makefile,v 1.2 2025/11/06 16:13:24 adam Exp $

.include "../../databases/sqlite3/Makefile.common"

DISTNAME=	sqlite-src-${SQLITE3_DISTVERSION}
PKGNAME=	sqlite3-diff-${SQLITE3_VERSION}
CATEGORIES=	databases
EXTRACT_SUFX=	.zip

MAINTAINER=	schmonz@NetBSD.org
COMMENT=	Display content differences between SQLite databases

HAS_CONFIGURE=	yes

BUILD_TARGET=	sqldiff

INSTALLATION_DIRS=	bin

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "IRIX"
# configure finds pread64/pwrite64 by linking, but <unistd.h> declares
# them only under _SGIAPI, which sqlite3.c's _XOPEN_SOURCE turns off.
SUBST_CLASSES+=		pread64
SUBST_STAGE.pread64=	post-configure
SUBST_MESSAGE.pread64=	Dropping HAVE_PREAD64 and HAVE_PWRITE64.
SUBST_FILES.pread64=	sqlite_cfg.h
SUBST_SED.pread64=	-e "/HAVE_PREAD64/d" -e "/HAVE_PWRITE64/d"
# configure finds -lpthread for pthread_mutexattr_init, but the sqldiff
# rule does not link it.
LDFLAGS+=		-lpthread
.endif

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/sqldiff ${DESTDIR}${PREFIX}/bin

.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
