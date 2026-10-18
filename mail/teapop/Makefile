# $NetBSD: Makefile,v 1.53 2023/10/24 22:09:51 wiz Exp $

DISTNAME=	teapop-0.3.8
PKGREVISION=	24
CATEGORIES=	mail
MASTER_SITES=	# ftp://ftp.toontown.org/pub/teapop/

MAINTAINER=	dawszy@arhea.net
#HOMEPAGE=	http://www.toontown.org/teapop/
COMMENT=	Yet another RFC1939 compliant POP3 server

USE_TOOLS+=	perl:run

GNU_CONFIGURE=		YES

CONFIGURE_ARGS+=	--sysconfdir=${PKG_SYSCONFDIR:Q}
CONFIGURE_ARGS+=	--enable-piddir=${VARBASE}/run

.include "../../mk/bsd.fast.prefs.mk"
# configure checks that the pid directory exists, and looks for the mail
# spool, on the build host. IRIX's spool is /var/mail.
CONFIGURE_ARGS.IRIX+=	--enable-mailspool=/var/mail
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=		piddir
SUBST_STAGE.piddir=	pre-configure
SUBST_FILES.piddir=	config/configure
SUBST_SED.piddir=	-e 's,^elif test -d $$pop_piddir; then$$,elif true; then,'
.endif

EGDIR=		${PREFIX}/share/examples/teapop
CONF_FILES=	${EGDIR}/teapop.passwd ${PKG_SYSCONFDIR}/teapop.passwd

RCD_SCRIPTS=	teapop

.include "options.mk"

INSTALLATION_DIRS+=	${EGDIR}

post-install:
	${INSTALL_DATA} ${WRKSRC}/etc/teapop.passwd ${DESTDIR}${EGDIR}

.include "../../security/tcp_wrappers/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
