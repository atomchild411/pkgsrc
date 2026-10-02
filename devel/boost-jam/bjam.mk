# $NetBSD: bjam.mk,v 1.27 2025/12/25 22:45:28 adam Exp $

.include "../../devel/boost-build/toolset.mk"

TOOL_DEPENDS+=	boost-jam>=${BOOST_VERSION:U0}:../../devel/boost-jam

BJAM=		${TOOLBASE}/bin/b2

BJAM_ARGS+=	${MAKE_JOBS:D-j${MAKE_JOBS}}
BJAM_ARGS+=	--builddir=${WRKSRC}/build
BJAM_ARGS+=	--layout=system
BJAM_ARGS+=	--toolset=${BOOST_TOOLSET}
BJAM_ARGS+=	${BJAM_BUILD}

# XXX: we can't use USE_LANGUAGES here as it needs to be set before
# including compiler.mk.  Perhaps we should just enforce c++14?
#
.include "../../mk/compiler.mk"

.if !empty(PKGSRC_COMPILER:Mclang)
BJAM_ARGS+=	cxxflags=-std=c++14
CXXFLAGS+=	-std=c++14
.  if ${OPSYS} == "Darwin"
BJAM_ARGS+=	cxxflags=-stdlib=libc++ linkflags=-stdlib=libc++
.  endif
.endif

# b2's name for IRIX. It defaults to the build host's system: a cross build
# was Linux to it (boost.log then asks for _XOPEN_SOURCE=600).
.if ${OPSYS} == "IRIX"
BJAM_BUILD+=	target-os=sgi
.endif
BJAM_BUILD+=	variant=release
BJAM_BUILD+=	threading=multi
BJAM_BUILD+=	link=shared,static
BJAM_BUILD+=	linkflags=${LDFLAGS:Q}

BJAM_CMD=	${SETENV} ${MAKE_ENV} ${BJAM} ${BJAM_ARGS}

UNLIMIT_RESOURCES+=	datasize

bjam-build:
	${_ULIMIT_CMD} \
	cd ${WRKSRC} && ${BJAM_CMD} --prefix=${PREFIX} stage

bjam-install:
	${_ULIMIT_CMD} \
	cd ${WRKSRC} && ${BJAM_CMD} --prefix=${DESTDIR}${PREFIX} install
