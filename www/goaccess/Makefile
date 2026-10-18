# $NetBSD: Makefile,v 1.41 2026/09/02 19:04:58 wiz Exp $

DISTNAME=	goaccess-1.9
PKGREVISION=	2
CATEGORIES=	www
MASTER_SITES=	https://tar.goaccess.io/

MAINTAINER=	wiedi@frubar.net
HOMEPAGE=	https://goaccess.io/
COMMENT=	Real-time web log analyzer and viewer
LICENSE=	gnu-gpl-v2

TOOL_DEPENDS+=	gettext-tools-[0-9]*:../../devel/gettext-tools

GNU_CONFIGURE=	yes

USE_LANGUAGES=	c99
USE_TOOLS+=	pkg-config aclocal autoconf automake

USE_CURSES=	getmouse
FAKE_NCURSES=	yes

EGDIR=		${PREFIX}/share/examples/${PKGBASE}
CONF_FILES=	${EGDIR}/goaccess.conf ${PKG_SYSCONFDIR}/goaccess.conf

LIBS.SunOS+=		-lsocket -lnsl
CPPFLAGS.SunOS+=	-D__EXTENSIONS__
LDFLAGS.NetBSD+=	-lterminfo

BROKEN_GETTEXT_DETECTION=	yes

.include "../../mk/bsd.prefs.mk"

GOACCESS_USER?=		${APACHE_USER}
GOACCESS_GROUP?=	${APACHE_GROUP}

BUILD_DEFS+=		VARBASE GOACCESS_USER GOACCESS_GROUP

PKG_USERS_VARS=		GOACCESS_USER
PKG_GROUPS_VARS=	GOACCESS_GROUP
PKG_GROUPS=		${GOACCESS_GROUP}
PKG_USERS=		${GOACCESS_USER}:${GOACCESS_GROUP}

RCD_SCRIPTS+=		goaccess
FILES_SUBST+=		GOACCESS_USER=${GOACCESS_USER:Q}

.include "options.mk"

.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# The build runs bin2c, which it builds, to embed the HTML report's files:
# build one for the build host too, and run that.
SUBST_CLASSES+=		bin2c
SUBST_STAGE.bin2c=	pre-build
SUBST_MESSAGE.bin2c=	Running a build-host bin2c.
SUBST_FILES.bin2c=	Makefile
SUBST_SED.bin2c=	-e 's,^\([[:space:]]*\)\./bin2c ,\1${WRKDIR}/bin2c-native ,'
pre-build: goaccess-bin2c-native
.PHONY: goaccess-bin2c-native
goaccess-bin2c-native:
	${RUN} ${NATIVE_CC} -O2 -o ${WRKDIR}/bin2c-native ${WRKSRC}/src/bin2c.c
.endif

pre-configure:
	cd ${WRKSRC} && autoreconf -fiv

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../devel/glib2/buildlink3.mk"
.include "../../mk/curses.buildlink3.mk"
.include "../../mk/terminfo.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
