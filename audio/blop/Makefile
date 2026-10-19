# $NetBSD: Makefile,v 1.7 2026/08/04 20:28:43 wiz Exp $
#

DISTNAME=	blop-0.2.8
PKGREVISION=	1
CATEGORIES=	audio
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=blop/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://blop.sourceforge.net/
COMMENT=	Bandlimited LADSPA Oscillator Plugins
LICENSE=	gnu-gpl-v2

GNU_CONFIGURE=		yes
USE_PKGLOCALEDIR=	yes

CONFIGURE_ARGS+=	--with-ladspa-prefix=${BUILDLINK_PREFIX.ladspa}

# FIXME: replace by proper LDFLAGS handling
_WRAP_EXTRA_ARGS.CC+=	${_RELRO_LDFLAGS}
_WRAP_EXTRA_ARGS.CXX+=	${_RELRO_LDFLAGS}
CWRAPPERS_PREPEND.cc+=	${_RELRO_LDFLAGS}
CWRAPPERS_PREPEND.cxx+=	${_RELRO_LDFLAGS}

.include "../../mk/bsd.fast.prefs.mk"
# The build runs wavegen to write the wave tables (C source): build it for
# the build host.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		wavegen
SUBST_STAGE.wavegen=	pre-configure
SUBST_FILES.wavegen=	src/Makefile.in
SUBST_SED.wavegen=	-e 's|^	\$$(wavegen_LINK) .*|	${NATIVE_CC} -I${BUILDLINK_DIR}/include -Iinclude -I. -I.. -o $$@ wavegen.c wdatutil.c -lm|'
.endif

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../audio/ladspa/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
