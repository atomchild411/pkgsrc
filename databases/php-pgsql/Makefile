# $NetBSD: Makefile,v 1.20 2025/02/08 03:11:26 taca Exp $

MODNAME=		pgsql
PKGREVISION=		1
CATEGORIES+=		databases
COMMENT=		PHP extension for PostgreSQL databases

CONFLICTS=	php-pgsql-[0-9]*

# The directory pg_config is in (in a cross build, the buildlink one).
CONFIGURE_ARGS+=	--with-${MODNAME}=shared,${PGSQL_PG_CONFIG:H:H}

.include "../../lang/php/ext.mk"
.include "../../mk/pgsql.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
