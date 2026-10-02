# $NetBSD: IRIX.mk,v 1.45 2025/04/12 08:36:35 nia Exp $
#
# Variable definitions for the IRIX operating system.

ECHO_N?=	${ECHO} -n
IMAKE_MAKE?=	${MAKE}		# program which gets invoked by imake
IMAKEOPTS+=	-DMakeCmd=${PREFIX}/bin/bmake -DProjectRoot=${X11BASE}
IMAKEOPTS+=	-DManUsr=${PREFIX}
# A cross build runs the build host's imake: have its preprocessor see
# IRIX, so that it picks sgi.cf, rather than the build host.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
IMAKEOPTS+=	-Ulinux -U__linux -U__linux__ -U__gnu_linux__ -U__GLIBC__
IMAKEOPTS+=	-U__NetBSD__ -U__APPLE__ -U__MACH__
IMAKEOPTS+=	-U__amd64__ -U__x86_64__ -U__i386__ -U__aarch64__ -U__arm64__
IMAKEOPTS+=	-Dsgi -D__sgi -Dmips -D__mips
IMAKEOPTS+=	-DOSMajorVersion=${OS_VERSION:R} -DOSMinorVersion=${OS_VERSION:E}
.endif
# sgi.cf is written for MIPSpro. With clang: the compiler by its usual
# name, none of MIPSpro's options, pkgsrc's install, and no -cckr for the
# preprocessor (sgi.cf sets CppCmd unconditionally).
.if ${PKGSRC_COMPILER:U:Mclang}
IMAKEOPTS+=	-DCcCmd=cc -DDefaultCCOptions= -DInstallCmd=${INSTALL}
BUILDLINK_TRANSFORM+=	rm:-cckr
.endif
.if empty(OS_VERSION:M6*)
IMAKEOPTS+=	-DShLibDir=${X11BASE}/lib
IMAKEOPTS+=	-DOptimizerLevel="${CFLAGS}"
IMAKEOPTS+=	-DManPath=${PREFIX}/man
.endif
# crypt(3) is in libc; IRIX has no libcrypt for -lcrypt to find.
BUILDLINK_TRANSFORM+=	rm:-lcrypt
PKGLOCALEDIR?=	share
PS?=		/sbin/ps
SU?=		/sbin/su
TYPE?=		/sbin/type

CPP_PRECOMP_FLAGS?=	# unset
DEF_UMASK?=		022
DEFAULT_SERIAL_DEVICE?=	/dev/null
EXPORT_SYMBOLS_LDFLAGS?=	# Don't add symbols to the dynamic symbol table
MOTIF_TYPE_DEFAULT?=	dt		# default 2.0 compatible libs type
NOLOGIN?=		${FALSE}
ROOT_CMD?=		${SU} - root -c
ROOT_GROUP?=		sys
ROOT_USER?=		root
SERIAL_DEVICES?=	/dev/null
ULIMIT_CMD_datasize?=	ulimit -d `ulimit -H -d`
ULIMIT_CMD_stacksize?=	ulimit -s `ulimit -H -s`
ULIMIT_CMD_memorysize?=	ulimit -v `ulimit -H -v`

USERADD?=		${LOCALBASE}/sbin/useradd
GROUPADD?=		${LOCALBASE}/sbin/groupadd
_PKG_USER_HOME?=	/dev/null # to match other system accounts
_USER_DEPENDS=		user-irix>=20130712:../../sysutils/user_irix

_OPSYS_EMULDIR.irix=	# empty

_OPSYS_SYSTEM_RPATH?=	/usr/lib${LIBABISUFFIX}
_OPSYS_LIB_DIRS?=	/usr/lib${LIBABISUFFIX} /lib${LIBABISUFFIX}
_OPSYS_INCLUDE_DIRS?=	/usr/include

.if exists(/usr/include/netinet6)
_OPSYS_HAS_INET6=	yes		# IPv6 is standard
.else
_OPSYS_HAS_INET6=	no		# IPv6 is not standard
.endif
_OPSYS_HAS_JAVA=	no		# Java is not standard
_OPSYS_HAS_MANZ=	no		# no MANZ for gzipping of man pages
_OPSYS_PTHREAD_AUTO=	no		# -lpthread needed for pthreads
_OPSYS_SHLIB_TYPE=	ELF		# shared lib type
.if defined(_OPSYS_GPATCH_REQD) && ${_OPSYS_GPATCH_REQD} == "YES"
_PATCH_CAN_BACKUP=	yes		# patch(1) can make backups
_PATCH_BACKUP_ARG?=	-b -V simple -z # switch to patch(1) for backup suffix
.else
_PATCH_CAN_BACKUP=	no		# native patch(1) can make backups
.endif
_USE_RPATH=		yes		# add rpath to LDFLAGS

# IRIX has /usr/include/iconv.h, but it's not GNU iconv, so mark it
# incompatible.
_INCOMPAT_ICONV=	IRIX-*-*

_STRIPFLAG_CC?=		${_INSTALL_UNSTRIPPED:D:U-s}	# cc(1) option to strip
_STRIPFLAG_INSTALL?=	${_INSTALL_UNSTRIPPED:D:U-S -f}	# install(1) option to strip

PKG_TOOLS_BIN?=		${LOCALBASE}/sbin

CONFIGURE_ENV+=		ABI=${ABI:Q}
MAKE_ENV+=		ABI=${ABI:Q}

LIBABISUFFIX?=		${ABI}

_OPSYS_CAN_CHECK_SHLIBS=	no # can't use readelf in check/bsd.check-vars.mk

# check for maximum command line length and set it in configure's environment,
# to avoid a test required by the libtool script that takes forever.
_OPSYS_MAX_CMDLEN_CMD=	/usr/sbin/sysconf ARG_MAX

# The C++ library is LLVM's libc++, which leaves out what C++17 and C++20
# removed (auto_ptr, unary_function, bind1st, random_shuffle, ...) when a
# program is built for them, as clang builds C++ by default. libstdc++,
# which most packages are written against, keeps them: keep them here too.
.for _f_ in CXX17_REMOVED_AUTO_PTR CXX17_REMOVED_BINDERS \
	CXX17_REMOVED_RANDOM_SHUFFLE CXX17_REMOVED_UNARY_BINARY_FUNCTION \
	CXX17_REMOVED_UNEXPECTED_FUNCTIONS CXX20_REMOVED_BINDER_TYPEDEFS \
	CXX20_REMOVED_NEGATORS CXX20_REMOVED_RAW_STORAGE_ITERATOR \
	CXX20_REMOVED_SHARED_PTR_UNIQUE CXX20_REMOVED_TEMPORARY_BUFFER \
	CXX20_REMOVED_TYPE_TRAITS CXX20_REMOVED_UNCAUGHT_EXCEPTION
CWRAPPERS_PREPEND.cxx+=	-D_LIBCPP_ENABLE_${_f_}
.endfor
