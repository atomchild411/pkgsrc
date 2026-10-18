# $NetBSD: Makefile,v 1.42 2026/08/07 09:12:28 wiz Exp $

.include "../../www/nghttp2/Makefile.common"

PKGNAME=	${DISTNAME:S/-/-tools-/}

COMMENT=	Tools for nghttp2

CONFLICTS+=	nghttp2<1.53.0nb1 # share/nghttp2/fetch-ocsp-response

# The distfile contains a C library (built via www/nghttp2) and tools
# (built by this package).
USE_LANGUAGES=		c c++20
USE_LIBTOOL=		yes
USE_TOOLS+=		gmake pkg-config
GNU_CONFIGURE=		yes
CONFIGURE_ARGS+=	--disable-examples
CONFIGURE_ARGS+=	--disable-python-bindings
CONFIGURE_ARGS+=	--enable-app
CONFIGURE_ARGS+=	--enable-hpack-tools

# for '#include <print>'
GCC_REQD+=		14

# C++23 std::unexpected (for std::expected) collides with the old
# std::unexpected() that mk/platform/IRIX.mk keeps libc++ declaring.
CXXFLAGS.IRIX+=		-U_LIBCPP_ENABLE_CXX17_REMOVED_UNEXPECTED_FUNCTIONS

.include "../../mk/bsd.prefs.mk"
.if ${OPSYS} == "IRIX"
# LOG_AUTHPRIV and LOG_FTP are LOG_AUTH's and LOG_DAEMON's values on IRIX:
# drop their duplicate cases from the facility-to-name switch (names still
# parse to them).
SUBST_CLASSES+=		syslog
SUBST_STAGE.syslog=	pre-configure
SUBST_MESSAGE.syslog=	Dropping duplicate syslog facility cases.
SUBST_FILES.syslog=	src/shrpx_config.cc
SUBST_SED.syslog=	-e '/^  case (LOG_AUTHPRIV):$$/,/^    return "authpriv"sv;$$/d'
SUBST_SED.syslog+=	-e '/^  case (LOG_FTP):$$/,/^    return "ftp"sv;$$/d'
.endif

INSTALL_DIRS+=		src

REPLACE_PYTHON+=	script/fetch-ocsp-response

.include "../../devel/libev/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../net/libcares/buildlink3.mk"
.include "../../net/ngtcp2/buildlink3.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../textproc/jansson/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../www/nghttp2/buildlink3.mk"
.include "../../www/nghttp3/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
