# $NetBSD: Makefile,v 1.3 2022/09/27 20:32:56 fcambus Exp $

DISTNAME=	trader-7.18
CATEGORIES=	games
MASTER_SITES=	https://ftp.zap.org.au/pub/trader/unix/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.zap.org.au/projects/trader/
COMMENT=	Simple text-based game of interstellar trading
LICENSE=	gnu-gpl-v3

GNU_CONFIGURE=		yes
USE_PKGLOCALEDIR=	yes

# IRIX's struct lconv has the C89 fields only, all trader uses: gnulib's
# replacement struct would need its localeconv module, which trader does
# not import.
CONFIGURE_ENV.IRIX+=	gl_cv_sys_struct_lconv_ok=yes

.include "../../devel/gettext-lib/buildlink3.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../mk/curses.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
