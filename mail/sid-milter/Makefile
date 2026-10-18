# $NetBSD: Makefile,v 1.14 2025/11/17 11:01:06 wiz Exp $

DISTNAME=	sid-milter-1.0.0
PKGREVISION=	7
CATEGORIES=	mail
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=sid-milter/}

MAINTAINER=	pkgsrc-users@NetBSD.org
#HOMEPAGE=	https://sid-milter.sourceforge.net/
COMMENT=	Open source SPF/SenderID filter software from Sendmail, Inc
LICENSE=	sendmail-open-source-license

USE_TOOLS+=		gm4
MAKE_ENV+=		M4=${M4:Q}
PTHREAD_OPTS+=		require
RCD_SCRIPTS=		sid-filter

SIDDOC=		${PREFIX}/share/doc/sid-milter

SUBST_CLASSES+=		libs
SUBST_STAGE.libs=	pre-build
SUBST_FILES.libs=	sid-filter/Makefile.m4
SUBST_SED.libs=		-e "s|@LMBASE@|${BUILDLINK_PREFIX.libmilter}|g"
SUBST_MESSAGE.libs=	Fixing paths.

INSTALLATION_DIRS=	bin include lib ${PKGMANDIR}/man3 ${PKGMANDIR}/man8

.include "../../mk/bsd.fast.prefs.mk"

post-extract:
	${CP} ${FILESDIR}/sid-filter.m4 ${WRKSRC}/sid-filter/Makefile.m4
.if ${OPSYS} == "IRIX"
	# devtools/OS/IRIX.6.5 has MIPSpro's options in confCC (-mips3 -n32
	# -OPT:Olimit=0): the compiler's defaults and the wrappers' flags instead.
	${ECHO} "define(\`confCC', \`cc')" >> ${WRKSRC}/devtools/Site/site.config.m4
	# conf.h's IRIX section predates unsetenv; the toolchain provides it.
	${ECHO} "APPENDDEF(\`confENVDEF', \`-DHASUNSETENV=1')" \
	    >> ${WRKSRC}/devtools/Site/site.config.m4
.endif

do-build:
	(cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ./Build)

# obj.* is the one directory Build made (named from the target's uname -srm,
# which a cross build's ${UNAME} is not).
do-install:
	${INSTALL_DATA_DIR} ${DESTDIR}${SIDDOC}
	${INSTALL_LIB} ${WRKSRC}/obj.*/libmarid/sm-marid.h \
		${DESTDIR}${PREFIX}/include
	${INSTALL_LIB} ${WRKSRC}/obj.*/libar/libar.a \
		${DESTDIR}${PREFIX}/lib
	${INSTALL_MAN} ${WRKSRC}/libar/ar.3 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man3/
	${INSTALL_PROGRAM} ${WRKSRC}/obj.*/sid-filter/sid-filter \
		${DESTDIR}${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/sid-filter/sid-filter.8 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man8/
	${INSTALL_DATA} ${WRKSRC}/FEATURES ${DESTDIR}${SIDDOC}
	${INSTALL_DATA} ${WRKSRC}/INSTALL ${DESTDIR}${SIDDOC}
	${INSTALL_DATA} ${WRKSRC}/KNOWNBUGS ${DESTDIR}${SIDDOC}
	${INSTALL_DATA} ${WRKSRC}/LICENSE ${DESTDIR}${SIDDOC}
	${INSTALL_DATA} ${WRKSRC}/README ${DESTDIR}${SIDDOC}
	${INSTALL_DATA} ${WRKSRC}/README-SenderID ${DESTDIR}${SIDDOC}
	${INSTALL_DATA} ${WRKSRC}/RELEASE_NOTES ${DESTDIR}${SIDDOC}
	${INSTALL_DATA} ${WRKSRC}/rfc4406.txt ${DESTDIR}${SIDDOC}
	${INSTALL_DATA} ${WRKSRC}/rfc4407.txt ${DESTDIR}${SIDDOC}
	${INSTALL_DATA} ${WRKSRC}/rfc4408.txt ${DESTDIR}${SIDDOC}

.include "../../security/openssl/buildlink3.mk"
.include "../../mail/libmilter/buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
