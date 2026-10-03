# $NetBSD: Makefile,v 1.97 2026/08/21 09:38:08 wiz Exp $

.include "Makefile.common"

PKGNAME=	clang-${LLVM_VERSION}
PKGREVISION=	3

COMMENT=	C language family frontend for LLVM

USE_TOOLS+=	perl:run

# Certain header files are generated, and can only be generated
# if llvm has support for the target.
PLIST_VARS+=	RISCV
.if ${PKG_BUILD_OPTIONS.llvm:Mllvm-target-riscv}
PLIST.RISCV=	yes
.endif

PLIST_VARS+=	ARM
.if	${PKG_BUILD_OPTIONS.llvm:Mllvm-target-arm} ||	\
	${PKG_BUILD_OPTIONS.llvm:Mllvm-target-aarch64}
PLIST.ARM=	yes
.endif

# libclang-cpp.so uses connect(), socket(), ...
LDFLAGS.SunOS+=	-lsocket

# clang-tblgen turns the .td files into source while clang builds. A cross
# build has to run the build host's, so install it (as lang/llvm installs
# llvm-tblgen) and take both from this package built for the host.
post-install:
	${INSTALL_PROGRAM} ${CMAKE_BUILD_DIR}/bin/clang-tblgen ${DESTDIR}${PREFIX}/bin

.if ${USE_CROSS_COMPILE:U:tl} == "yes"
TOOL_DEPENDS+=		clang>=${LLVM_VERSION}nb3:../../lang/clang
CMAKE_CONFIGURE_ARGS+=	-DLLVM_TABLEGEN_EXE:FILEPATH=${TOOLBASE:Q}/bin/llvm-tblgen
CMAKE_CONFIGURE_ARGS+=	-DLLVM_NATIVE_TOOL_DIR:PATH=${TOOLBASE:Q}/bin
.endif

.include "../../mk/atomic64.mk"
.include "../../mk/bsd.pkg.mk"
