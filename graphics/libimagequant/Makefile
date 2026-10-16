# $NetBSD: Makefile,v 1.42 2025/11/16 08:43:40 adam Exp $

DISTNAME=	libimagequant-4.4.1
CATEGORIES=	graphics
MASTER_SITES+=	${MASTER_SITE_GITHUB:=ImageOptim/}
GITHUB_TAG=	${PKGVERSION_NOREV}

MAINTAINER=	adam@NetBSD.org
HOMEPAGE=	https://pngquant.org/lib/
COMMENT=	High-quality conversion of RGBA images to 8-bit indexed-color
LICENSE=	gnu-gpl-v3

TOOL_DEPENDS+=	cargo-c>=0.9.27:../../devel/cargo-c

WRKSRC=		${WRKDIR}/${DISTNAME}/imagequant-sys

PKGCONFIG_OVERRIDE=		${DESTDIR}${PREFIX}/lib/pkgconfig/imagequant.pc
PKGCONFIG_OVERRIDE_STAGE=	post-install

.include "cargo-depends.mk"

# cargo-c with cargo.mk's environment and arguments (in a cross build they
# name the target, and the build host's linker for build scripts).
do-install:
	${RUN} cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${CARGO} cinstall --release \
		${DEFAULT_CARGO_ARGS} --destdir=${DESTDIR} --prefix=${PREFIX} \
		--libdir=${PREFIX}/lib

.include "../../lang/rust/cargo.mk"
.include "../../mk/bsd.pkg.mk"
