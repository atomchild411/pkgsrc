# $NetBSD: Makefile,v 1.21 2018/05/08 08:17:36 wen Exp $
#

DISTNAME=	apachetop-0.18.4
CATEGORIES=	sysutils www
MASTER_SITES=	${MASTER_SITE_GITHUB:=tessus/apachetop/archive/}
DISTFILES=	0.18.4.zip

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/tessus/apachetop
COMMENT=	Real time apache log display
LICENSE=	modified-bsd

GNU_CONFIGURE=		YES
CONFIGURE_ARGS+=	--with-logfile=${VARBASE}/log/httpd/access_log
USE_LANGUAGES=		c c++
USE_TOOLS+=		autoconf automake
# IRIX has <fam.h> but the sysroot has no libfam.
CONFIGURE_ENV.IRIX+=	ac_cv_header_fam_h=no

pre-configure:
	(cd ${WRKSRC}; ./autogen.sh)

.include "../../mk/curses.buildlink3.mk"
.include "../../mk/readline.buildlink3.mk"
.include "../../mk/pthread.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
