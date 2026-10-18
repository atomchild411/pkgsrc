# $NetBSD: Makefile,v 1.58 2023/11/12 13:23:34 wiz Exp $
#

DISTNAME=	lavaps-2.7
PKGREVISION=	20
CATEGORIES=	sysutils x11
MASTER_SITES=	http://www.isi.edu/~johnh/SOFTWARE/LAVAPS/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.isi.edu/~johnh/SOFTWARE/LAVAPS/
COMMENT=	Lava lamp of currently running processes

MAKE_JOBS_SAFE=		no

USE_LANGUAGES=	c c++
USE_TOOLS+=	perl pod2man pod2html gmake

GNU_CONFIGURE=		YES
CONFIGURE_ARGS+=	--with-tcltk \
			--with-tcl-ver=8.6.1 \
			--with-tk-ver=8.6.1 \
			--with-tcltk-lib-suffix-type=nodot

# prevents the GConf schema from going into / when building the tcl/tk version
MAKE_ENV+=	PKGSRC_INSTALL_SCHEMAS=no

BUILDLINK_DEPMETHOD.libXt?=	build

CFLAGS.NetBSD+=	-D_KMEMUSER

.include "../../x11/tk/buildlink3.mk"
.include "../../lang/tcl/buildlink3.mk"
.include "../../x11/libSM/buildlink3.mk"
.include "../../x11/libICE/buildlink3.mk"
.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.include "../../x11/libX11/buildlink3.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# src/ runs tcl2cc, which the build makes, to embed the Tcl code: build one
# for the build host too, and run that.
SUBST_CLASSES+=		tcl2cc
SUBST_STAGE.tcl2cc=	pre-build
SUBST_MESSAGE.tcl2cc=	Running a build-host tcl2cc.
SUBST_FILES.tcl2cc=	src/Makefile
SUBST_SED.tcl2cc=	-e 's,\.\./tcl2cc/tcl2cc lava,${WRKDIR}/tcl2cc-native lava,'
pre-build: lavaps-tcl2cc-native
.PHONY: lavaps-tcl2cc-native
lavaps-tcl2cc-native:
	${RUN} ${NATIVE_CC} -O2 -include stdlib.h -o ${WRKDIR}/tcl2cc-native ${WRKSRC}/tcl2cc/tcl2cc.c
.endif

.include "../../mk/bsd.pkg.mk"
