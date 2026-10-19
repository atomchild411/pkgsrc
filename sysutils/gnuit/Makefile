# $NetBSD: Makefile,v 1.6 2025/12/23 07:48:01 wiz Exp $

DISTNAME=	gnuit-4.9.5
PKGREVISION=	1
CATEGORIES=	misc
MASTER_SITES=	${MASTER_SITE_GNU:=git/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.gnu.org/software/gnuit/
COMMENT=	GNU Interactive Tools - a file system browser for UNIX systems
LICENSE=	gnu-gpl-v3

GNU_CONFIGURE=		YES
CONFIGURE_ARGS+=	--htmldir=${PREFIX}/share/doc/gnuit
CONFIGURE_ARGS+=	--disable-transition
INFO_FILES=		YES

# gnulib's putenv replacement loses its rpl_putenv name to the IRIX
# <stdlib.h> wrapper (nested through IRIX's <getopt.h> include, see
# toolchain-ideas 45); gnuit only adds variables with putenv, which IRIX's
# does.
CONFIGURE_ENV.IRIX+=	gl_cv_func_svid_putenv=yes

post-extract:
	${CP} ${WRKSRC}/term/gnuitrc.ansi.in ${WRKSRC}/term/gnuitrc.cons25.in

.include "../../mk/termcap.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
