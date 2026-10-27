# $NetBSD: Makefile,v 1.63 2026/07/23 20:10:39 tnn Exp $

.include "../../devel/gettext/Makefile.common"

PKGNAME=	${DISTNAME:S/-/-lib-/}
PKGREVISION=	2
COMMENT=	Internationalized Message Handling Library (libintl)

USE_LANGUAGES=		c
CONFIGURE_ARGS+=	--with-included-gettext
CONFIGURE_ARGS+=	--with-included-libintl
CONFIGURE_ARGS+=	--disable-csharp
CONFIGURE_ARGS+=	--disable-c++
CONFIGURE_ENV+=		PKGLOCALEDIR=${PKGLOCALEDIR}
# IRIX: libintl takes its locks with pthread functions (from libc's stubs
# or libpthread) but did not need libpthread, so IRIX's rld could run its
# users' init code before libpthread's: when a program loads libpthread
# ahead of them, libgpg-error's init (bindtextdomain) crashed in
# pthread_cond_broadcast, so every threaded libgcrypt user died before
# main. Needing libpthread puts its init first.
LIBS.IRIX+=		-lpthread
MAKE_ENV+=		PKGLOCALEDIR=${PKGLOCALEDIR}
GNU_CONFIGURE_STRICT=	no # because of gettext-tools/examples

CFLAGS+=		${CFLAGS.${ICONV_TYPE}-iconv}
CFLAGS.gnu-iconv+=	-DHAVE_GNU_ICONV

INSTALL_MAKE_FLAGS=	${MAKE_FLAGS} localedir=${EGDIR}
INSTALL_MAKE_FLAGS+=	includedir=${PREFIX}/include/gettext

BUILD_DIRS=		gettext-runtime/intl

.include "../../converters/libiconv/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
