# $NetBSD: Makefile,v 1.3 2025/09/27 09:57:15 wiz Exp $

PKGREVISION= 1
.include "Makefile.common"

COMMENT=	Cross-language data serialization

CONFIGURE_ARGS+=	--disable-libs

.include "../../devel/boost-headers/buildlink3.mk"

# The tutorial (not installed) runs the thrift just built, which a cross
# build cannot.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
CONFIGURE_ARGS+=	--disable-tutorial --disable-tests
.endif
.include "../../mk/bsd.pkg.mk"
