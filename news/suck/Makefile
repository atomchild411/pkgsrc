# $NetBSD: Makefile,v 1.44 2023/10/24 22:10:40 wiz Exp $
#

DISTNAME=	suck-4.3.2
PKGREVISION=	15
CATEGORIES=	news
MASTER_SITES=	${MASTER_SITE_SUNSITE:=system/news/transport/}

MAINTAINER=	pkgsrc-users@NetBSD.org
#failed 20120718
#HOMEPAGE=	http://home.comcast.net/~bobyetman/
COMMENT=	Feed a local news server without a dedicated newsfeed

GNU_CONFIGURE=	yes
USE_FEATURES=	snprintf
TOOLS_BROKEN+=	perl

MAKE_JOBS_SAFE=		no

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# makephrases, run at build time to write phrases.h, is for the build host.
SUBST_CLASSES+=		makephr
SUBST_STAGE.makephr=	pre-configure
SUBST_FILES.makephr=	Makefile.in
SUBST_SED.makephr=	-e 's|^	\$$(CC) \$$(LDFLAGS) -o makephrases \$$(makepobjs) \$$(LIBS)|	${NATIVE_CC} $$(DEFS) -I. -o makephrases makephrases.c suck_phrases.c rpost_phrases.c test_phrases.c both_phrases.c lmove_phrases.c|'
.endif

.include "options.mk"

post-patch:
	${SED} -e 's|%%%HISTORY%%%|${PREFIX}/etc/news/history|g' \
		${WRKSRC}/Makefile.in >${WRKSRC}/Makefile.tmp
	@${MV} ${WRKSRC}/Makefile.tmp ${WRKSRC}/Makefile.in

INSTALLATION_DIRS+=	share/examples/suck
INSTALL_MAKE_FLAGS+=	prefix=${DESTDIR}${PREFIX} \
			mandir=${DESTDIR}${PREFIX}/${PKGMANDIR}/man1

post-install:
	${INSTALL_DATA} ${WRKSRC}/sample/* ${DESTDIR}${PREFIX}/share/examples/suck

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "Linux"
.include "../../databases/gdbm_compat/buildlink3.mk"
.endif

.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
