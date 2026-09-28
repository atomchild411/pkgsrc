# $NetBSD: Makefile,v 1.28 2026/09/02 19:03:59 wiz Exp $

DISTNAME=	libsoup-3.6.6
PKGNAME=	${DISTNAME:S/soup/soup3/}
PKGREVISION=	2
CATEGORIES=	net gnome
MASTER_SITES=	${MASTER_SITE_GNOME:=sources/libsoup/${PKGVERSION_NOREV:R}/}
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://wiki.gnome.org/Projects/libsoup
COMMENT=	HTTP library implementation in C (major version 3)
LICENSE=	gnu-lgpl-v2

DEPENDS+=	glib-networking-[0-9]*:../../net/glib-networking
# not found by meson
#TOOL_DEPENDS+=	${PYPKGPREFIX}-gi-docgen-[0-9]*:../../devel/py-gi-docgen

# 2 test failures as of 3.6.5

USE_CC_FEATURES=	c99
USE_LANGUAGES=		c
USE_TOOLS+=		msgfmt pkg-config

PKGCONFIG_OVERRIDE+=		output/meson-private/libsoup-3.0.pc
PKGCONFIG_OVERRIDE_STAGE=	pre-install

# disable vala detection
MESON_ARGS+=	-Dvapi=disabled
# disable sysprof, not shipped in subprojects and gets git cloned otherwise
MESON_ARGS+=	-Dsysprof=disabled

TEST_ENV+=	LD_LIBRARY_PATH=${WRKSRC}/output/libsoup
TEST_ENV+=	LD_LIBRARY_PATH=${WRKSRC}/output/tests
# for Darwin
TEST_ENV+=	DYLD_LIBRARY_PATH=${WRKSRC}/output/libsoup
TEST_ENV+=	DYLD_LIBRARY_PATH=${WRKSRC}/output/tests

PYTHON_FOR_BUILD_ONLY=		tool

.include "options.mk"

# prevent spurious git cloning of gi-docgen in configure stage
post-extract:
	rm -f ${WRKSRC}/subprojects/*.wrap

.include "../../archivers/brotli/buildlink3.mk"
.include "../../databases/sqlite3/buildlink3.mk"
BUILDLINK_API_DEPENDS.glib2+=	glib2>=2.69.1
.include "../../devel/glib2/buildlink3.mk"
.include "../../devel/meson/build.mk"
.include "../../lang/python/tool.mk"
# A cross build cannot run the tests (GnuTLS is only for the PKCS #11 ones)
# nor the program that checks glib-networking provides TLS.
.if ${USE_CROSS_COMPILE:tl} == "yes"
MESON_ARGS+=	-Dtests=false -Dpkcs11_tests=disabled -Dtls_check=false
.else
.  include "../../security/gnutls/buildlink3.mk"
.endif
.include "../../www/libpsl/buildlink3.mk"
.include "../../www/nghttp2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
