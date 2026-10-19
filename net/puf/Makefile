# $NetBSD: Makefile,v 1.11 2025/11/17 11:01:16 wiz Exp $
#

DISTNAME=	puf-1.0.0
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=puf/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://puf.sourceforge.net/
COMMENT=	Parallel URL fetcher
LICENSE=	gnu-gpl-v2

GNU_CONFIGURE=	YES
# Run tests: IRIX has a 64-bit off_t and printf knows %lli.
CONFIGURE_ENV.IRIX+=	ob_cv_type_off_t_ll=yes
CONFIGURE_ENV.IRIX+=	ob_cv_func_printf_ok=yes

.include "../../mk/bsd.pkg.mk"
