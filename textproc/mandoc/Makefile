# $NetBSD: Makefile,v 1.19 2025/07/30 13:21:45 wiz Exp $

DISTNAME=	mandoc-1.14.6
PKGREVISION=	3
CATEGORIES=	textproc devel
MASTER_SITES=	http://mandoc.bsd.lv/snapshots/

MAINTAINER=	schwarze@usta.de
HOMEPAGE=	https://mandoc.bsd.lv/
COMMENT=	Convert man pages from mdoc, man, eqn and tbl to txt, html, ps, or pdf
LICENSE=	2-clause-bsd # not exactly, but near enough

HAS_CONFIGURE=	yes

SUBST_CLASSES+=		roff
SUBST_STAGE.roff=	pre-build
SUBST_FILES.roff=	mandoc.1 mandoc.3
SUBST_FILES.roff+=	eqn.7 man.7 mdoc.7 tbl.7
SUBST_SED.roff=		-e 's,Xr roff,Xr mandoc-roff,g'

#CFLAGS.NetBSD+=	-D_OPENBSD_SOURCE

USE_TOOLS+=	perl:test
TEST_TARGET=	regress

.include "../../mk/bsd.fast.prefs.mk"

post-extract:
	${ECHO} PREFIX=${PREFIX} > ${WRKSRC}/configure.local
	${ECHO} CFLAGS=\"${CFLAGS:Q}\" >> ${WRKSRC}/configure.local
	${ECHO} LDFLAGS=\"${LDFLAGS:Q}\" >> ${WRKSRC}/configure.local
	${ECHO} INSTALL=\"${INSTALL:Q}\" >> ${WRKSRC}/configure.local
	${ECHO} INSTALL_PROGRAM=\"${INSTALL_PROGRAM:Q}\" >> ${WRKSRC}/configure.local
	${ECHO} INSTALL_LIB=\"${INSTALL_DATA:Q}\" >> ${WRKSRC}/configure.local
	${ECHO} INSTALL_MAN=\"${INSTALL_MAN:Q}\" >> ${WRKSRC}/configure.local
	${ECHO} INSTALL_DATA=\"${INSTALL_DATA:Q}\" >> ${WRKSRC}/configure.local
	${ECHO} MANDIR="${PREFIX}/${PKGMANDIR}" >> ${WRKSRC}/configure.local
	${ECHO} MANM_ROFF="mandoc-roff" >> ${WRKSRC}/configure.local
	${ECHO} BINM_SOELIM="msoelim" >> ${WRKSRC}/configure.local

# configure compiles and runs a test program per feature, which a cross
# build cannot run: answer them for IRIX (libc plus what the toolchain's
# wrapper headers and compiler-rt add).
.if ${USE_CROSS_COMPILE:U:tl} == "yes" && ${OPSYS} == "IRIX"
MANDOC_HAVE=	WFLAG=1 STATIC=0 ATTRIBUTE=1 CMSG=0 DIRENT_NAMLEN=0 EFTYPE=0
MANDOC_HAVE+=	ENDIAN=0 SYS_ENDIAN=0 NTOHL=1 ERR=1 FTS=1 FTS_COMPARE_CONST=1
MANDOC_HAVE+=	GETLINE=1 GETSUBOPT=1 ISBLANK=1 MKDTEMP=1 MKSTEMPS=1
MANDOC_HAVE+=	NANOSLEEP=1 O_DIRECTORY=1 OHASH=0 PATH_MAX=1 PLEDGE=0
MANDOC_HAVE+=	PROGNAME=0 REALLOCARRAY=1 RECALLOCARRAY=0 RECVMSG=1
MANDOC_HAVE+=	REWB_BSD=0 REWB_SYSV=0 SANDBOX_INIT=0 STRCASESTR=1
MANDOC_HAVE+=	STRINGLIST=0 STRLCAT=1 STRLCPY=1 STRNDUP=1 STRPTIME=1 STRSEP=1
MANDOC_HAVE+=	STRTONUM=1 VASPRINTF=1 WCHAR=0
pre-configure:
.  for h in ${MANDOC_HAVE}
	${ECHO} HAVE_${h} >> ${WRKSRC}/configure.local
.  endfor
.endif

.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
