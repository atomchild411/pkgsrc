# $NetBSD$
#
# clang, lld and libc++ for IRIX 6.5 (n32), from a prebuilt tree.
#
# The tree is built outside pkgsrc, by tools/irix-cross/llvm/build-llvm.sh
# (the LLVM 21 port on llvm-project's iris/main): its "package" stage writes
# pkgsrc-clang-VERSION-irix65-n32.tar.gz, laid out for /opt/pkgsrc.  This
# package takes that file from CLANG_IRIX_DIST (a local directory; set in
# mk.conf) and installs it into PREFIX as it is.
#
# The distfile is ours and changes with every toolchain build, so there is
# no distinfo (NO_CHECKSUM), and "fetching" links DISTDIR's copy to the
# file in CLANG_IRIX_DIST, so a new build is picked up without a stale copy.
# Its PLIST is generated from the tarball (see the README of the overlay);
# regenerate it if a new build adds or removes files.

DISTNAME=	pkgsrc-clang-${CLANG_IRIX_VERSION}-irix65-n32
PKGNAME=	clang-irix-${CLANG_IRIX_VERSION}
# nb1: the IRIX header wrappers work against a stock 6.5.22 root too.
# nb2: lld reads SGI's own relocatable objects (llvm iris/main 349c3a1);
# new header wrappers.
# nb3: lld handles R_MIPS_LITERAL, R_MIPS_PJUMP and puts .sbss before .bss
# (llvm iris/main 39fc2ba): every n32 archive in /usr/lib32 links.
# nb4: the builtins' libc stand-ins are weak, so a program's own copy wins
# (llvm iris/main 369bd58).
PKGREVISION=	4
CATEGORIES=	lang
MASTER_SITES=	# none: see do-fetch
DIST_SUBDIR=	clang-irix

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://llvm.org/
COMMENT=	Clang 21, lld and libc++ for IRIX 6.5 (n32), prebuilt
# LLVM, clang, lld, libc++, libc++abi, libunwind and compiler-rt are all
# "Apache-2.0 WITH LLVM-exception"; pkgsrc names that apache-2.0 (as for
# lang/clang, lang/libcxx).
LICENSE=	apache-2.0

CLANG_IRIX_VERSION=	21.1.8

.include "../../mk/bsd.prefs.mk"

CLANG_IRIX_DIST?=	/nonexistent/set-CLANG_IRIX_DIST-in-mk.conf

ONLY_FOR_PLATFORM=	IRIX-*-*
NO_CHECKSUM=		yes
NO_CONFIGURE=		yes
NO_BUILD=		yes
USE_LANGUAGES=		# none: nothing is compiled
USE_TOOLS+=		pax
# The tools are stripped and the archives are as built; leave them alone.
STRIP_DEBUG_SUPPORTED=	no
CHECK_SHLIBS_SUPPORTED=	no

# The same files as these packages' (bin/clang, lib/clang/21, include/c++/v1,
# lib/libc++*, lib/libunwind*, ...).
CONFLICTS+=	clang-[0-9]* lld-[0-9]* llvm-[0-9]* libLLVM-[0-9]*
CONFLICTS+=	libcxx-[0-9]* libcxxabi-[0-9]* libunwind-[0-9]*
CONFLICTS+=	compiler-rt-[0-9]*

WRKSRC=		${WRKDIR}/opt/pkgsrc

# A build-tree leftover in some tarballs, not part of the toolchain.
NOT_INSTALLED=	lib/clang/21/lib/mips64-sgi-irix6.5/libclang_rt.builtins.a.pre-compat

do-fetch:
	${RUN}src=${CLANG_IRIX_DIST:Q}/${DISTFILES:Q};			\
	[ -f "$$src" ] || ${FAIL_MSG} "$$src not found: build it (tools/irix-cross/llvm/build-llvm.sh package) or set CLANG_IRIX_DIST"; \
	${MKDIR} ${_DISTDIR:Q};						\
	${LN} -sf "$$src" ${_DISTDIR:Q}/${DISTFILES:Q}

do-install:
	cd ${WRKSRC} && ${PAX} -rw -pp . ${DESTDIR}${PREFIX}
	${RM} -f ${DESTDIR}${PREFIX}/${NOT_INSTALLED}

.include "../../mk/bsd.pkg.mk"
