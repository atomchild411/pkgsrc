# $NetBSD$

PKGNAME=	clang-irix-libs-${CLANG_IRIX_VERSION}
# nb2: the runtimes of llvm iris/main 68d432f448 (weak libc stand-ins,
# select/pselect, net/if.h, setgroups wrappers, MIPS fake_use).
# nb1: the runtimes of the toolchain from llvm iris/main 2edcdfb: the
# 2026-10-02 build this package still had lacked symbols that programs
# linked since bound to it, and rld refused to start them (exit 1).  Bump
# this whenever the cross toolchain's runtimes are rebuilt.
PKGREVISION=	6
CATEGORIES=	lang
MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://libcxx.llvm.org/
COMMENT=	C++ runtime of clang for IRIX (libc++, libc++abi, libunwind)
LICENSE=	apache-2.0

CLANG_IRIX_VERSION=	21.1.8

# What IRIX machines need to run C++ programs built with clang: the
# shared libc++, libc++abi and libunwind of the toolchain they were built
# with (mk/compiler/clang.mk makes every C++ package depend on this one).
# Like gccNN-libs for gcc.  The compiler and the files for building
# against these libraries are lang/clang-irix.
ONLY_FOR_PLATFORM=	IRIX-*-*
NO_CONFIGURE=		yes
NO_BUILD=		yes
USE_LANGUAGES=		c++	# for the compiler that is asked where they are
STRIP_DEBUG_SUPPORTED=	no
CONFLICTS+=		libcxx-[0-9]* libcxxabi-[0-9]* libunwind-[0-9]*

IRIX_RUNTIME_LIBS=	libc++.so.1.0 libc++abi.so.1.0 libunwind.so.1.0

INSTALLATION_DIRS=	lib

.include "../../mk/bsd.prefs.mk"

.if ${USE_CROSS_COMPILE:tl} == "yes"
# A cross build packages the libraries the cross compiler links against:
# programs built with it then find the same ones on IRIX.
DISTFILES=		# none
_IRIX_RUNTIME_DIR_cmd=	${PKG_CXX} -print-file-name=libc++.so.1.0
IRIX_RUNTIME_DIR=	${_IRIX_RUNTIME_DIR_cmd:sh:H}
do-extract:
	${MKDIR} ${WRKSRC}/lib
.  for l in ${IRIX_RUNTIME_LIBS}
	${CP} ${IRIX_RUNTIME_DIR}/${l} ${WRKSRC}/lib/${l}
.  endfor
.else
# On IRIX, from the prebuilt toolchain lang/clang-irix is made from.
DISTNAME=		pkgsrc-clang-${CLANG_IRIX_VERSION}-irix65-n32
DIST_SUBDIR=		clang-irix
MASTER_SITES=		# none: see do-fetch
NO_CHECKSUM=		yes
CLANG_IRIX_DIST?=	/nonexistent/set-CLANG_IRIX_DIST-in-mk.conf
WRKSRC=			${WRKDIR}/opt/pkgsrc
do-fetch:
	${RUN}src=${CLANG_IRIX_DIST:Q}/${DISTFILES:Q};			\
	[ -f "$$src" ] || ${FAIL_MSG} "$$src not found: build it (tools/irix-cross/llvm/build-llvm.sh package) or set CLANG_IRIX_DIST"; \
	${MKDIR} ${_DISTDIR:Q};						\
	${LN} -sf "$$src" ${_DISTDIR:Q}/${DISTFILES:Q}
.endif

do-install:
.for l in ${IRIX_RUNTIME_LIBS}
	${INSTALL_LIB} ${WRKSRC}/lib/${l} ${DESTDIR}${PREFIX}/lib/${l}
	${LN} -sf ${l} ${DESTDIR}${PREFIX}/lib/${l:R}
.endfor

.include "../../mk/bsd.pkg.mk"
