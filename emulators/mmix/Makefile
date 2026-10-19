# $NetBSD: Makefile,v 1.33 2026/08/04 20:28:54 wiz Exp $

DISTNAME=	mmix-20060918
PKGREVISION=	1
CATEGORIES=	emulators devel lang
MASTER_SITES=	https://www-cs-faculty.stanford.edu/~knuth/programs/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www-cs-faculty.stanford.edu/~knuth/mmix.html
COMMENT=	Simulators for Knuth's MMIX RISC architecture

TOOL_DEPENDS+=	dvipsk-[0-9]*:../../print/dvipsk
TOOL_DEPENDS+=	tex-cweb-[0-9]*:../../print/tex-cweb
TOOL_DEPENDS+=	tex-epsf-[0-9]*:../../print/tex-epsf
TOOL_DEPENDS+=	tex-tex-[0-9]*:../../print/tex-tex

MAKE_JOBS_SAFE=		no

WRKSRC=		${WRKDIR}
BUILD_TARGET=	all doc

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# The build runs abstime to write abstime.h (the build time): use a copy
# built for the build host; the target's is still installed.
SUBST_CLASSES+=		abstime
SUBST_STAGE.abstime=	pre-configure
SUBST_FILES.abstime=	Makefile
SUBST_SED.abstime=	-e 's|^	./abstime > abstime.h|	${NATIVE_CC} -std=gnu89 -o abstime-host abstime.c \&\& ./abstime-host > abstime.h|'
.endif

INSTALLATION_DIRS=	bin

do-install:
	cd ${WRKSRC} && ${INSTALL_PROGRAM} abstime mmix mmixal 		\
		mmmix mmotype ${DESTDIR}${PREFIX}/bin
	${INSTALL_DATA_DIR} ${DESTDIR}${PREFIX}/share/doc/mmix
	cd ${WRKSRC} && ${INSTALL_DATA} README *.ps 			\
		${DESTDIR}${PREFIX}/share/doc/mmix
	${INSTALL_DATA_DIR} ${DESTDIR}${PREFIX}/share/examples/mmix
	cd ${WRKSRC} && ${INSTALL_DATA} *.mms *.mmix *.mmconfig 	\
		${DESTDIR}${PREFIX}/share/examples/mmix

# FIXME: replace by proper LDFLAGS handling
_WRAP_EXTRA_ARGS.CC+=	${_RELRO_LDFLAGS}
_WRAP_EXTRA_ARGS.CXX+=	${_RELRO_LDFLAGS}
CWRAPPERS_PREPEND.cc+=	${_RELRO_LDFLAGS}
CWRAPPERS_PREPEND.cxx+=	${_RELRO_LDFLAGS}

.include "../../mk/bsd.pkg.mk"
