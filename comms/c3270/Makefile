# $NetBSD: Makefile,v 1.5 2025/11/26 08:37:09 wiz Exp $

DISTNAME=	suite3270-4.1ga11-src
PKGNAME=	c3270-4.1ga11
PKGREVISION=	2
CATEGORIES=	comms
MASTER_SITES=	https://x3270.bgp.nu/download/04.01/
EXTRACT_SUFX=	.tgz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://x3270.bgp.nu/
COMMENT=	3270 Terminal emulator for ncurses
LICENSE=	modified-bsd

WRKSRC=			${WRKDIR}/suite3270-4.1
CONFLICTS=		x3270-[0-9]*
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--enable-c3270

.include "../../mk/bsd.fast.prefs.mk"
# The build runs helpers it compiles: lib/3270's mkicon (make's default
# rule) turns favicon.ico into C; c3270's mkfb compiles the fallbacks and
# mkkeypad the keypad description. Build them for the build host (mkfb
# includes the generated conf.h).
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		c3270helpers
SUBST_STAGE.c3270helpers=	pre-configure
SUBST_FILES.c3270helpers=	c3270/Makefile.obj.in
SUBST_SED.c3270helpers=	-e 's|^\t$$(CC) $$(CFLAGS) $$(LDFLAGS) -o $$@ $$(filter %.c,$$^)$$|\t${NATIVE_CC} -I. -I$$(THIS) -I$$(TOP)/Common/c3270 -I$$(TOP)/Common -I$$(TOP)/include -o $$@ $$(filter %.c,$$^)|'
SUBST_SED.c3270helpers+=	-e 's,^keypad.o: compiled_keypad.h$$,mkkeypad: mkkeypad.c\n\t${NATIVE_CC} -o $$@ $$<\n\n&,'
SUBST_CLASSES+=		mkicon
SUBST_STAGE.mkicon=	pre-configure
SUBST_FILES.mkicon=	lib/3270/Makefile.obj.in
SUBST_SED.mkicon=	-e 's,^favicon.c: favicon.ico mkicon$$,mkicon: mkicon.c\n\t${NATIVE_CC} -o $$@ $$<\n\n&,'
.endif
USE_TOOLS+=		gmake pkg-config

PKG_SYSCONFSUBDIR=	x3270
EGDIR=			share/examples/c3270
INSTALLATION_DIRS+=	${EGDIR}
CONF_FILES+=		${EGDIR}/ibm_hosts ${PKG_SYSCONFDIR}/ibm_hosts

post-install:
	${MV} ${DESTDIR}${PKG_SYSCONFDIR}/ibm_hosts ${DESTDIR}${PREFIX}/${EGDIR}


.include "../../converters/libiconv/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../textproc/expat/buildlink3.mk"
.include "../../lang/tcl/buildlink3.mk"
.include "../../devel/ncurses/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
