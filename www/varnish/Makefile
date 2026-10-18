# $NetBSD: Makefile,v 1.52 2026/09/02 19:05:02 wiz Exp $

DISTNAME=	varnish-7.7.1
PKGREVISION=	2
CATEGORIES=	www
MASTER_SITES=	https://varnish-cache.org/_downloads/
EXTRACT_SUFX=	.tgz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://varnish-cache.org/
COMMENT=	High-performace HTTP accelerator
LICENSE=	modified-bsd

TOOL_DEPENDS+=	${PYPKGPREFIX}-docutils>=0.12:../../textproc/py-docutils
TOOL_DEPENDS+=	${PYPKGPREFIX}-sphinx-[0-9]*:../../textproc/py-sphinx

PYTHON_VERSIONS_INCOMPATIBLE=	310 311 # py-sphinx

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes
USE_TOOLS+=	pkg-config gmake

BUILD_DEFS+=	VARBASE
BUILD_DEFS+=	PKG_SYSCONFBASE

PKG_SYSCONFSUBDIR=	varnish
EGDIR=			${PREFIX}/share/examples/varnish
CONF_FILES=		${EGDIR}/builtin.vcl \
			${PKG_SYSCONFDIR}/builtin.vcl

.include "../../mk/bsd.prefs.mk"

VRNUSER?=		varnish
VRNGROUP?=		${VRNUSER}
STATEDIR=		${VARBASE}/db
VRNDIR=			${STATEDIR}/${PKGBASE}

OWN_DIRS+=		${VRNDIR}
OWN_DIRS_PERMS+=	${VRNDIR} ${VRNUSER} ${VRNGROUP} 0770

PKG_GROUPS+=		${VRNGROUP}
PKG_USERS+=		${VRNUSER}:${VRNGROUP}
PKG_HOME.${VRNUSER}=	${VRNDIR}
PKG_SHELL.${VRNUSER}=	${SH}
PKG_GECOS.${VRNUSER}=	Varnish daemon user

FILES_SUBST+=		VRNUSER=${VRNUSER}
FILES_SUBST+=		VRNGROUP=${VRNGROUP}

REPLACE_PYTHON+=	lib/libvcc/vmodtool.py
REPLACE_PYTHON+=	lib/libvsc/vsctool.py

CONFIGURE_ARGS+=	--localstatedir=${STATEDIR}
CONFIGURE_ARGS+=	--sysconfdir=${PKG_SYSCONFBASE}
CONFIGURE_ARGS+=	--with-rst2html=${TOOLBASE}/bin/rst2html-${PYVERSSUFFIX}
CONFIGURE_ARGS+=	--with-rst2man=${TOOLBASE}/bin/rst2man-${PYVERSSUFFIX}
# Run tests: IRIX has none of these socket options, nor close_range().
CONFIGURE_ENV.IRIX+=	ac_cv_have_tcp_keep=no ac_cv_have_tcp_keepalive=no
CONFIGURE_ENV.IRIX+=	ac_cv_have_tcp_fastopen=no ac_cv_have_working_close_range=no

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# The build runs vhp_gen_hufdec (vhp_hufdec.h) and varnishstat_help_gen:
# build them for the build machine as well (with libvarnish's VSB, and a
# VAS_Fail of their own).
SUBST_CLASSES+=		gens
SUBST_STAGE.gens=	pre-configure
SUBST_MESSAGE.gens=	Running the build machine's generators.
SUBST_FILES.gens=	bin/varnishd/Makefile.in bin/varnishstat/Makefile.in
SUBST_SED.gens=		-e 's,$$(AM_V_GEN) \./vhp_gen_hufdec >,$$(AM_V_GEN) ${WRKDIR}/vhp_gen_hufdec >,'
SUBST_SED.gens+=	-e 's,$$(AM_V_GEN) \./varnishstat_help_gen >,$$(AM_V_GEN) ${WRKDIR}/varnishstat_help_gen >,'
pre-build: varnish-host-gens
.PHONY: varnish-host-gens
varnish-host-gens:
	${NATIVE_CC} -I${WRKSRC}/include -I${WRKSRC} -o ${WRKDIR}/vhp_gen_hufdec \
	    ${WRKSRC}/bin/varnishd/hpack/vhp_gen_hufdec.c ${FILESDIR}/vas-stub.c
	cd ${WRKSRC}/bin/varnishstat && ${NATIVE_CC} -I${WRKSRC}/include \
	    -I${WRKSRC} -I. -o ${WRKDIR}/varnishstat_help_gen \
	    varnishstat_help_gen.c ${WRKSRC}/lib/libvarnish/vsb.c \
	    ${FILESDIR}/vas-stub.c
.endif
CONFIGURE_ARGS+=	--with-sphinx-build=${PREFIX}/bin/sphinx-build-${PYVERSSUFFIX}

# Explicitly disable epoll on illumos, provided for Linux compat only.
CONFIGURE_ARGS.SunOS+=	--disable-epoll

SUBST_CLASSES+=		edit
SUBST_SED.edit+=	-e s,editline/readline.h,readline.h,
SUBST_FILES.edit+=	bin/varnishadm/varnishadm.c configure
SUBST_MESSAGE.edit=	Fix path to libedit header for pkgsrc.
SUBST_STAGE.edit=	pre-configure

.include "../../mk/compiler.mk"

# Fixes build on at least SunOS/i386
# See https://github.com/varnishcache/varnish-cache/issues/1875
.if ${CC_VERSION:Mgcc*} && ${MACHINE_ARCH} == "i386"
CFLAGS+=		-fexcess-precision=standard
.endif
LDFLAGS.NetBSD+=	-lm	# for ldexp

INSTALL_MAKE_FLAGS+=	sysconfdir=${EGDIR}

# not signed/unsigned char safe
BUILDLINK_TRANSFORM+=	rm:-Werror

PKGCONFIG_OVERRIDE+=	varnishapi.pc.in

RCD_SCRIPTS=		varnishd varnishlog varnishncsa

TEST_TARGET=		check

.include "../../devel/pcre2/buildlink3.mk"
.include "../../devel/libexecinfo/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../mk/curses.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/readline.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
