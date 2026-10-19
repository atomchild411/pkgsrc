# $NetBSD: Makefile,v 1.15 2026/02/08 10:53:11 wiz Exp $

DISTNAME=	shorten-3.6.1
CATEGORIES=	audio archivers
#MASTER_SITES=	http://www.etree.org/shnutils/shorten/dist/src/

MAINTAINER=	pkgsrc-users@NetBSD.org
#HOMEPAGE=	http://www.etree.org/shnutils/shorten/
COMMENT=	Lossless audio compressor
LICENSE=	shorten-license

GNU_CONFIGURE=	YES

INSTALLATION_DIRS+=	share/doc/shorten

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# mkbshift writes the bitshift.h tables during the build: make them with
# one built for the build host.
post-configure:
	cd ${WRKSRC}/src && ${NATIVE_CC} -DHAVE_STDARG_H -DHAVE_STRERROR \
		'-DVERSION="${PKGVERSION_NOREV}"' -I.. -I../include \
		-o ${WRKDIR}/mkbshift ../utils/Sulawalaw.c ../utils/array.c \
		../utils/exit.c ../utils/mkbshift.c && ${WRKDIR}/mkbshift
.endif

post-install:
	${INSTALL_DATA} ${WRKSRC}/doc/tr156.tex ${DESTDIR}${PREFIX}/share/doc/shorten
	${INSTALL_DATA} ${WRKSRC}/doc/tr156.ps ${DESTDIR}${PREFIX}/share/doc/shorten

.include "../../mk/bsd.pkg.mk"
