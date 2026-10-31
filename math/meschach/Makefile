# $NetBSD: Makefile,v 1.20 2019/12/20 00:02:06 joerg Exp $

DISTNAME=		mesch12b
PKGNAME=		meschach-1.2b
PKGREVISION=		2
CATEGORIES=		math
MASTER_SITES=		http://www.math.uiowa.edu/~dstewart/meschach/

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		http://www.math.uiowa.edu/~dstewart/meschach/
COMMENT=		Library of C Routines for Matrix Computations

WRKSRC=			${WRKDIR}
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--with-all

.include "../../mk/bsd.fast.prefs.mk"
# configure runs macheps (double and float epsilon) and maxint: IEEE
# values and a 32-bit int, the same on the build host, so build them there.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		probes
SUBST_STAGE.probes=	pre-configure
SUBST_FILES.probes=	configure
SUBST_SED.probes=	-e 's,^$$CC -o macheps ,${NATIVE_CC} -std=gnu89 -o macheps ,'
SUBST_SED.probes+=	-e 's,^$$CC -o maxint ,${NATIVE_CC} -std=gnu89 -o maxint ,'
.endif
MAKE_FILE=		makefile
USE_BSD_MAKEFILE=	yes
MAKE_FLAGS+=		MKPROFILE=yes

INSTALLATION_DIRS=	include/meschach lib share/meschach/tests

BUILDLINK_TRANSFORM+=	rm:-Werror

pre-patch:
	${CP} ${FILESDIR}/makefile.in ${WRKSRC}

post-patch:
	${SED} -e 's:@PREFIX@:'${PREFIX}':g' ${FILESDIR}/makefile.test 	\
		> ${WRKSRC}/Makefile

post-install:
	cd ${WRKSRC} && ${INSTALL_DATA} err.h machine.h matlab.h 	\
		matrix.h meminfo.h sparse.h zmatrix.h iter.h matrix2.h 	\
		oldnames.h sparse2.h zmatrix2.h ${DESTDIR}${PREFIX}/include/meschach/
	cd ${WRKSRC} && ${INSTALL_DATA} torture.c sptort.c ztorture.c 	\
		memtort.c itertort.c mfuntort.c iotort.c 		\
		${DESTDIR}${PREFIX}/share/meschach/tests/
	${INSTALL_DATA} ${WRKSRC}/Makefile ${DESTDIR}${PREFIX}/share/meschach/tests
	cd ${WRKSRC} && ${INSTALL_DATA} README ./DOC/* 			\
		${DESTDIR}${PREFIX}/share/meschach/
	${INSTALL_DATA} ${WRKSRC}/copyright ${DESTDIR}${PREFIX}/share/meschach
	cd ${WRKSRC} && ${INSTALL_DATA} tutadv.c tutorial.c		\
		${DESTDIR}${PREFIX}/share/meschach/

.include "../../mk/bsd.prefs.mk"

# IRIX: bsd.lib.mk links shared libraries with ld -nostdlib; add the compiler
# runtime, which holds the libc add-ons (__irix_*) that the objects call.
.if ${OPSYS} == "IRIX"
MAKE_FLAGS+=	SHLIB_LDENDFILE="$$(${CC} -print-libgcc-file-name)"
.endif

.include "../../mk/bsd.pkg.mk"
