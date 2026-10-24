# $NetBSD: Makefile,v 1.11 2026/01/08 14:17:47 taca Exp $

MODNAME=		opcache
PKGREVISION=		1
CATEGORIES+=		devel
COMMENT=		PHP extension for opcode caching

PHP_ZEND_EXTENSION=	yes
CONFIGURE_ARGS+=	--enable-${MODNAME}=opcache
USE_PHP_EXT_PATCHES=	Yes

# Ensure libgcc's __builtin_cpu_* stuff is pulled in.
LDFLAGS.SunOS+=	-lgcc
# configure runs a program to find shared memory, which a cross build
# cannot: IRIX has System V shared memory.
CONFIGURE_ENV.IRIX+=	php_cv_shm_ipc=yes

# PHP 8.5 bundles opcache extension.
PHP_VERSIONS_ACCEPTED=	84 83 82 74 56

# PHP 8.4's opcache depends on gmake.
.include "../../lang/php/phpversion.mk"
.if ${PHP_VER} == 84
USE_TOOLS+=	gmake
.endif

TEST_TARGET=	test

.include "../../lang/php/ext.mk"
.include "../../mk/bsd.pkg.mk"
