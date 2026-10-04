# $NetBSD: rust.mk,v 1.20 2026/04/04 18:48:49 tnn Exp $
#
# This file determines the type of rust package to use.
#
# It should be included by rust-dependent packages that don't use
# cargo.mk.
#
# === User-settable variables ===
#
# RUST_TYPE
#	The preferred type of Rust release to use - either build from source,
#	or use a binary installation.
#
#	Official Rust binaries are only published for certain platforms.  The
#	"bin" option uses the lang/rust-bin package, whereas "native" uses
#	binaries installed on the host system.  If using "native" with a rustup
#	installation, you will probably also need to set RUSTUP_HOME in your
#	MAKE_ENV pointing to the 'rustup show home' directory.  This is due to
#	pkgsrc overwriting the HOME environment variable during build.
#
#	Possible values: src bin native cross
#	Default: "src", except on 32-bit arm where it's "bin", and "cross"
#	when cross-compiling with RUST_CROSS_TARGET set
#
# RUST_CROSS_TARGET
#	When cross-compiling, the Rust target to build for (for example
#	mips64-sgi-irix). The build host's lang/rust must carry that
#	target's standard library (RUST_EXTRA_TARGETS there); Rust is then
#	a tool dependency, and cargo (by cargo.mk or a package's own build)
#	builds for the target: the target's C toolchain compiles and links
#	for it, the build host's builds build scripts and proc macros.
#
#	Default: unset
#
# RUST_CROSS_HOST
#	The build host's Rust target, when cross-compiling.
#
#	Default: derived from NATIVE_MACHINE_ARCH and NATIVE_OPSYS
#
# RUST_CROSS_CFLAGS
#	More C compiler flags for crates' C code built for the target
#	(cc-rs), e.g. definitions describing the target.
#
#	Default: empty
#
# === Package-settable variables ===
#
# RUST_REQ
#	The minimum version of Rust required by the package.
#
#	Default: 1.85.0
#
# RUST_RUNTIME
#	Whether rust is a runtime dependency.
#	Usually it is only needed to build.
#
#	Possible values: yes no
#	Default: no

.include "../../mk/bsd.fast.prefs.mk"
.include "platform.mk"

RUST_REQ?=	1.85.0
RUST_RUNTIME?=	no

.if ${USE_CROSS_COMPILE:U:tl} == "yes" && !empty(RUST_CROSS_TARGET)
RUST_TYPE?=	cross
.elif ${MACHINE_PLATFORM:M*-*-earm*}
RUST_TYPE?=	bin
.else
RUST_TYPE?=	src
.endif

.if ${RUST_TYPE} == "cross"
TOOL_DEPENDS+=	rust>=${RUST_REQ}:${RUST_DIR}
.  if ${NATIVE_OPSYS:U${OPSYS}} == "Linux"
RUST_CROSS_HOST?=	${NATIVE_MACHINE_ARCH:U${MACHINE_ARCH}}-unknown-linux-gnu
.  elif ${NATIVE_OPSYS:U${OPSYS}} == "NetBSD"
RUST_CROSS_HOST?=	${NATIVE_MACHINE_ARCH:U${MACHINE_ARCH}:S/^amd64$/x86_64/}-unknown-netbsd
.  endif
_RUST_CROSS_T=	${RUST_CROSS_TARGET:S/-/_/g}
_RUST_CROSS_H=	${RUST_CROSS_HOST:S/-/_/g}
ALL_ENV+=	CARGO_BUILD_TARGET=${RUST_CROSS_TARGET}
ALL_ENV+=	CARGO_TARGET_${_RUST_CROSS_T:tu}_LINKER=${CC:Q}
ALL_ENV+=	CARGO_TARGET_${_RUST_CROSS_H:tu}_LINKER=${NATIVE_CC:Q}
ALL_ENV+=	CC_${_RUST_CROSS_T}=${CC:Q}
ALL_ENV+=	CXX_${_RUST_CROSS_T}=${CXX:Q}
ALL_ENV+=	AR_${_RUST_CROSS_T}=${AR:Q}
ALL_ENV+=	CC_${_RUST_CROSS_H}=${NATIVE_CC:Q}
ALL_ENV+=	CXX_${_RUST_CROSS_H}=${NATIVE_CXX:Q}
ALL_ENV+=	HOST_CC=${NATIVE_CC:Q}
ALL_ENV+=	HOST_CXX=${NATIVE_CXX:Q}
# cc-rs takes CFLAGS_<target> over CFLAGS, and CFLAGS for the build host too
_RUST_CROSS_CFLAGS=	${CFLAGS} ${RUST_CROSS_CFLAGS}
ALL_ENV+=	CFLAGS_${_RUST_CROSS_T}=${_RUST_CROSS_CFLAGS:Q}
ALL_ENV+=	CXXFLAGS_${_RUST_CROSS_T}=${CXXFLAGS:Q}
ALL_ENV+=	HOST_CFLAGS=-O2
ALL_ENV+=	HOST_CXXFLAGS=-O2
# Crates patched for the target are local sources to cargo, so their own
# lint settings (deny(...)) apply: keep lints from failing a build.
RUSTFLAGS+=	--cap-lints=warn
ALL_ENV+=	RUSTFLAGS=${RUSTFLAGS:Q}
.endif

.if ${RUST_TYPE} == "bin"
.  if ${RUST_RUNTIME} == "no"
BUILDLINK_DEPMETHOD.rust-bin?=		build
.  endif
BUILDLINK_API_DEPENDS.rust-bin+=	rust-bin>=${RUST_REQ}
.  include "${RUST_DIR}-bin/buildlink3.mk"
.endif

.if ${RUST_TYPE} == "src"
.  if ${RUST_RUNTIME} == "no"
BUILDLINK_DEPMETHOD.rust?=		build
.  endif
BUILDLINK_API_DEPENDS.rust+=		rust>=${RUST_REQ}
.  include "${RUST_DIR}/buildlink3.mk"
.endif

.if ${OPSYS} == "NetBSD"
ALL_ENV+=	PTHREAD_KEYS_MAX=512
.endif
