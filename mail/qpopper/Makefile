# $NetBSD: Makefile,v 1.73 2026/08/03 13:12:29 wiz Exp $

DISTNAME=		qpopper${VERSION}
PKGNAME=		qpopper-${VERSION}
PKGREVISION=		7
CATEGORIES=		mail
MASTER_SITES=		${QPOPPER_MASTER_SITES}

PATCH_SITES=		${QPOPPER_PATCHSITES}
PATCHFILES=		${QPOPPER_PATCHFILES}

MAINTAINER=		mellon@fugue.com
HOMEPAGE=		${QPOPPER_HOMEPAGE}
COMMENT=		Qualcomm's POP server for Eudora

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes" && ${OPSYS} == "IRIX"
# configure looks for sendmail with test -f on the build host; IRIX's is
# /usr/lib/sendmail.
SUBST_CLASSES+=		sendmail
SUBST_STAGE.sendmail=	pre-configure
SUBST_FILES.sendmail=	configure
SUBST_SED.sendmail=	-e 's|^if test -f \$${sbindir}/sendmail$$|if false|'
SUBST_SED.sendmail+=	-e 's|^elif test -f /usr/sbin/sendmail$$|elif false|'
SUBST_SED.sendmail+=	-e 's|^elif test -f /usr/lib/sendmail$$|elif true|'
.endif

.include "Makefile.common"

CONFIGURE_ARGS+=	--enable-apop=${QPOPPER_APOP_AUTH:Q} \
			--enable-popuid=${QPOPPER_USER} \
			--disable-update-abort --without-gdbm

.include "options.mk"

QPOPPER_USER?=		pop
QPOPPER_GROUP?=		mail
QPOPPER_APOP_AUTH?=	${PKG_SYSCONFDIR}/apop.auth

BUILD_DEFS+=		QPOPPER_APOP_AUTH VARBASE
PKG_GROUPS_VARS+=	QPOPPER_GROUP
PKG_USERS_VARS+=	QPOPPER_USER

.if defined(QPOPPER_SPOOL_DIR)
CONFIGURE_ARGS+=	--enable-spool-dir=${QPOPPER_SPOOL_DIR}
.endif

RCD_SCRIPTS=		qpopper
MESSAGE_SUBST+=		RCD_SCRIPTS=${RCD_SCRIPTS} \
			RCD_SCRIPTS_DIR=${RCD_SCRIPTS_DIR}

PKG_USERS=		${QPOPPER_USER}:${QPOPPER_GROUP}

SUBST_CLASSES+=		prefix
SUBST_STAGE.prefix=	pre-configure
SUBST_FILES.prefix=	man/popper.8
SUBST_VARS.prefix=	PREFIX

SUBST_CLASSES+=		sysconf
SUBST_STAGE.sysconf=	pre-configure
SUBST_FILES.sysconf=	man/popauth.8
SUBST_VARS.sysconf=	PKG_SYSCONFDIR

SUBST_CLASSES+=		varbase
SUBST_STAGE.varbase=	pre-configure
SUBST_FILES.varbase=	popper/main.c
SUBST_VARS.varbase=	VARBASE

SPECIAL_PERMS+=		sbin/qpopauth ${QPOPPER_USER} ${REAL_ROOT_GROUP} 4511

INSTALLATION_DIRS=	libexec ${PKGMANDIR}/man8 sbin share/doc share/examples

post-install:
	${INSTALL_DATA} ${WRKSRC}/License.txt				\
		${DESTDIR}${PREFIX}/share/doc/qpopper.License
	${INSTALL_DATA} ${WRKSRC}/samples/qpopper.config		\
		 ${DESTDIR}${PREFIX}/share/examples

.include "../../mk/bsd.pkg.mk"
