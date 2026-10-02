# $NetBSD: Makefile,v 1.298 2026/09/19 19:18:02 wiz Exp $

.include "license.mk"
.include "Makefile.common"

PKGREVISION=	4

COMMENT=	Practical Extraction and Report Language

CONFLICTS+=	perl-base-[0-9]* perl-thread-[0-9]*

PATCHFILES+=	568e6fd238867bb9e99fa3f47cba3169009239e0.patch
PATCHFILES+=	54cf3d44cbbedd17d774e9a37921963e8fd5d0cb.patch
PATCH_SITES=	https://github.com/Perl/perl5/commit/

# when updating perl, you can remove packages that are included
# in perl core, see
# corelist -diff ${PREV_PKGVERSION} ${PKGVERSION}

SUPERSEDES+=	p5-Tie-File<=0.99
SUPERSEDES+=	p5-Time-HiRes-[0-9]*
SUPERSEDES+=	p5-DB_File-[0-9]*
SUPERSEDES+=	p5-Memoize<=1.03
SUPERSEDES+=	p5-I18N-LangTags<=0.39
SUPERSEDES+=	p5-Locale-Maketext<=1.23
SUPERSEDES+=	p5-experimental<=0.007

# XXX: requires that gcc use an external perl to avoid circular dependencies
USE_GCC_RUNTIME=	yes
USE_LANGUAGES=		c

.include "../../mk/bsd.prefs.mk"

# Determine the Perl API version from the patchlevel.h file from the
# source distribution.
#
PERL5_API_VERS=		${PERL5_API_VERS_cmd:sh}
PERL5_API_VERS_cmd=	\
	if ${TEST} -f ${WRKSRC}/patchlevel.h; then			\
		${AWK} '/\#define[ 	]*PERL_API_REVISION/ { R = $$3 }\
			/\#define[ 	]*PERL_API_VERSION/ { r = "."$$3 } \
			/\#define[ 	]*PERL_API_SUBVERSION/ { s = "."$$3 } \
			END { printf "%s%s%s\n", R, r, s }'		\
			${WRKSRC}/patchlevel.h;				\
	else								\
		${ECHO} "unknown";					\
	fi

.include "dirs.mk"

.include "../../mk/compiler.mk"

HAS_CONFIGURE=		yes
.if ${USE_CROSS_COMPILE:tl} == "yes"
# Perl's Configure runs the programs it compiles to learn about the target,
# which a cross build cannot: use perl-cross (github.com/arsv/perl-cross),
# a configure and Makefiles that only compile, laid over the perl source.
# It builds a miniperl for the build host to run the build with.  The
# choices Policy.sh makes for Configure are passed as -D options.
PERL_CROSS=		perl-cross-1.6.5
DISTFILES=		${DEFAULT_DISTFILES} ${PERL_CROSS}.tar.gz
SITES.${PERL_CROSS}.tar.gz= \
	https://github.com/arsv/perl-cross/releases/download/${PERL_CROSS:S/perl-cross-//}/
EXTRACT_ONLY=		${DEFAULT_DISTFILES}
USE_TOOLS+=		pax gzip gmake	# perl-cross's Makefiles are GNU make
CONFIGURE_SCRIPT=	./configure
CONFIGURE_ARGS+=	--target=${MACHINE_GNU_PLATFORM}
CONFIGURE_ARGS+=	--prefix=${PERL5_PREFIX}
# The target's headers, for the scans that read them (Errno); not left in
# Config.pm (post-install).
CONFIGURE_ARGS+=	--sysroot=${_CROSS_DESTDIR}
CONFIGURE_ARGS+=	--host-cc=${NATIVE_CC:Q}
CONFIGURE_ARGS+=	--with-cc=${CC:Q} --with-cpp=${CC:Q}\ -E
CONFIGURE_ARGS+=	--with-ar=${AR:Q} --with-ranlib=${RANLIB:Q}
CONFIGURE_ARGS+=	--with-objdump=${MACHINE_GNU_PLATFORM}-objdump
CONFIGURE_ARGS+=	-Dosname=${LOWER_OPSYS} -Dosvers=${OS_VERSION}
CONFIGURE_ARGS+=	-Darchname=${MACHINE_ARCH}-${LOWER_OPSYS}
# pkgsrc's flags go in optimize, so that ccflags keeps what perl-cross
# finds (the large-file defines, which its lseeksize/fpossize assume).
# -fwrapv and -fno-strict-aliasing, which perl needs from gcc and clang
# alike (Configure adds them for both), perl-cross adds only for a
# compiler it recognizes as gcc.
CONFIGURE_ARGS+=	-Doptimize=${CFLAGS:Q}\ -fwrapv\ -fno-strict-aliasing
CONFIGURE_ARGS+=	-Dldflags=${LDFLAGS:Q}
CONFIGURE_ARGS+=	-Dlibswanted=${LIBSWANTED:Q}
CONFIGURE_ARGS+=	-Dinstallstyle=lib/perl5 -Dinstallusrbinperl=undef
CONFIGURE_ARGS+=	-Di_malloc=undef
CONFIGURE_ARGS+=	-Dsiteprefix=${PERL5_SITEPREFIX}
CONFIGURE_ARGS+=	-Dvendorprefix=${PERL5_VENDORPREFIX}
CONFIGURE_ARGS+=	-Dscriptdir=${PERL5_PERLBASE}/bin
CONFIGURE_ARGS+=	-Dsitescript=${PERL5_SITEBASE}/bin
CONFIGURE_ARGS+=	-Dvendorscript=${PERL5_VENDORBASE}/bin
CONFIGURE_ARGS+=	-Dsitebin=${PERL5_SITEBIN}
CONFIGURE_ARGS+=	-Dvendorbin=${PERL5_VENDORBASE}/bin
CONFIGURE_ARGS+=	-Dprivlib=${PERL5_PRIVLIB}
CONFIGURE_ARGS+=	-Dsitelib=${PERL5_SITELIB}
CONFIGURE_ARGS+=	-Dvendorlib=${PERL5_VENDORLIB}
CONFIGURE_ARGS+=	-Dsitelib_stem=${PERL5_SITEBASE}
CONFIGURE_ARGS+=	-Dvendorlib_stem=${PERL5_VENDORBASE}
.  for _s_ in 1 3
CONFIGURE_ARGS+=	-Dman${_s_}ext=${_s_}
CONFIGURE_ARGS+=	-Dman${_s_}dir=${PERL5_PERLBASE}/${PKGMANDIR}/man${_s_}
CONFIGURE_ARGS+=	-Dsiteman${_s_}dir=${PERL5_SITEBASE}/${PKGMANDIR}/man${_s_}
CONFIGURE_ARGS+=	-Dvendorman${_s_}dir=${PERL5_VENDORBASE}/${PKGMANDIR}/man${_s_}
.  endfor
# The build's sysroot, out of what is installed: perl hands ccflags and
# ldflags to every module it builds on the target.
SUBST_CLASSES+=		sysroot
SUBST_STAGE.sysroot=	pre-install
SUBST_MESSAGE.sysroot=	Removing the build's sysroot from the Config files.
SUBST_FILES.sysroot=	lib/Config.pm lib/Config_heavy.pl lib/Config.pod
SUBST_SED.sysroot=	-e 's, *--sysroot=${_CROSS_DESTDIR},,g'
SUBST_SED.sysroot+=	-e "s,^sysroot='${_CROSS_DESTDIR}',sysroot='',"
SUBST_NOOP_OK.sysroot=	yes
# Where the tools are on the target, for what perl records and runs there.
.  for _t_ _v_ in sh SH sed SED ln LN
.    if defined(TARGET_TOOL.${_v_})
CONFIGURE_ARGS+=	-D${_t_}=${TARGET_TOOL.${_v_}:Q}
.    endif
.  endfor
.else
CONFIGURE_SCRIPT=	./Configure
CONFIGURE_ARGS+=	-sde
CONFIGURE_ARGS+=	-Dldflags=${LDFLAGS:Q}
.endif
MAKE_ENV+=		LC_ALL="C"
LDFLAGS.QNX+=		-lm

CONFIGURE_ARGS.SunOS+=	-Aundef:csh

# As of 5.44.0: All tests successful.
.if make(test)
ALLOW_NETWORK_ACCESS=	yes
.endif
TEST_TARGET=		test

# Policy.sh generation
# (see comments in files/Policy.sh)
SUBST_CLASSES+=		policysh
SUBST_STAGE.policysh=	pre-configure
SUBST_FILES.policysh=	Policy.sh
SUBST_VARS.policysh+=	MACHINE_ARCH
SUBST_VARS.policysh+=	LOWER_OPSYS
SUBST_VARS.policysh+=	OBJECT_FMT
SUBST_VARS.policysh+=	CC
SUBST_VARS.policysh+=	CFLAGS
SUBST_VARS.policysh+=	LDFLAGS
SUBST_VARS.policysh+=	COMPILER_RPATH_FLAG
SUBST_VARS.policysh+=	PERL5_PREFIX
SUBST_VARS.policysh+=	PERL5_SITEPREFIX
SUBST_VARS.policysh+=	PERL5_VENDORPREFIX
SUBST_VARS.policysh+=	PERL5_PERLBASE
SUBST_VARS.policysh+=	PERL5_SITEBASE
SUBST_VARS.policysh+=	PERL5_SITEBIN
SUBST_VARS.policysh+=	PERL5_VENDORBASE
SUBST_VARS.policysh+=	PERL5_PRIVLIB
SUBST_VARS.policysh+=	PERL5_SITELIB
SUBST_VARS.policysh+=	PERL5_VENDORLIB
SUBST_VARS.policysh+=	PKGMANDIR
SUBST_VARS.policysh+=	LOCALBASE
SUBST_VARS.policysh+=	PTHREAD_LDFLAGS

# Avoid the ${TOOLS_BIN} path getting written to installed files.
SUBST_CLASSES+=		toolsbin
SUBST_STAGE.toolsbin=	pre-configure
SUBST_FILES.toolsbin=	Configure
SUBST_VARS.toolsbin=	TOOLS_RM

SUBST_CLASSES+=		pwd
SUBST_STAGE.pwd=	pre-configure
SUBST_FILES.pwd=	dist/PathTools/Cwd.pm
SUBST_SED.pwd+=		-e "s,/bin/pwd,${TOOLS_PLATFORM.pwd},g"

.if ${OPSYS} == "Darwin" || ${OPSYS} == "Cygwin"
#
# The Perl build attempts to work around case-insensitivity problems on
# HFS filesystems by using GNUmakefiles, so we need to use GNU make.
#
USE_TOOLS+=	gmake
MAKE_FILE=	GNUmakefile
.endif

#
# For the moment disable the building of a shared libperl.dylib on Darwin
# => 9.0 as it breaks the build.  This should just be considered a temporary
# work around until the actual problem can be fixed as this worked for
# Darwin < 9.0.
#
.if !${MACHINE_PLATFORM:MDarwin-9.*-*}
CONFIGURE_ARGS+=	-Duseshrplib
.endif

# Perl embeds the full paths to the following tools in several installed
# files, so make sure the paths to the ones in ${TOOLS_DIR} aren't used.
#
USE_TOOLS+=		hostname ln rm sed test
SUBST_VARS.policysh+=	TOOLS_HOSTNAME_CMD
SUBST_VARS.policysh+=	TOOLS_LN
TOOLS_ALIASES.sed=	${TOOLS_SED:T}
SUBST_VARS.policysh+=	TOOLS_SED
SUBST_VARS.policysh+=	TOOLS_SH
SUBST_VARS.policysh+=	TOOLS_TEST
SUBST_VARS.policysh+=	FALSE

# Nail down the needed libraries for each platform here to avoid hidden
# dependencies.  If this isn't defined, then use the perl defaults for the
# particular operating system.
#
LIBSWANTED.Cygwin=	m crypt dl
LIBSWANTED.Darwin=	m c
LIBSWANTED.DragonFly=	m crypt
LIBSWANTED.FreeBSD=	m crypt
LIBSWANTED.Haiku=	network
LIBSWANTED.HPUX=	cl pthread $$libswanted # see Perl's README.hpux
LIBSWANTED.IRIX=	m crypt
LIBSWANTED.Linux=	m crypt dl nsl
LIBSWANTED.Minix=	m crypt c
LIBSWANTED.NetBSD=	m crypt
LIBSWANTED.OpenBSD=	m crypt
LIBSWANTED.SunOS=	m crypt dl socket nsl
LIBSWANTED.AIX=		m crypt dl socket nsl bind c
LIBSWANTED.SCO_SV=	m crypt socket
LIBSWANTED.UnixWare=	m crypt socket
LIBSWANTED=		${LIBSWANTED.${OPSYS}}
SUBST_VARS.policysh+=	LIBSWANTED

# Nail down the directories in which the system libraries may be found.
# If this isn't defined, then use the perl defaults for the particular
# operating system.
#
SYSLIBPATH.Cygwin=	/usr/lib
SYSLIBPATH.Darwin=	/usr/lib
SYSLIBPATH.DragonFly=	/usr/lib
SYSLIBPATH.FreeBSD=	/usr/lib
SYSLIBPATH.Minix=	/usr/lib
SYSLIBPATH.NetBSD=	/usr/lib
SYSLIBPATH.OpenBSD=	/usr/lib
SYSLIBPATH.SunOS=	/usr/lib
SYSLIBPATH.AIX=		/usr/lib
SYSLIBPATH.SCO_SV=	/usr/lib
SYSLIBPATH=		${SYSLIBPATH.${OPSYS}:U${COMPILER_LIB_DIRS}}
SUBST_VARS.policysh+=	SYSLIBPATH

.include "../../mk/dlopen.buildlink3.mk"
.include "options.mk"

# Replace our perl as the interpreter
REPLACE_PERL+=		cpan/Getopt-Long/lib/Getopt/Long.pm
REPLACE_PERL+=		dist/ExtUtils-ParseXS/lib/ExtUtils/xsubpp
REPLACE_PERL+=		ext/ExtUtils-Miniperl/lib/ExtUtils/Miniperl.pm
REPLACE_PERL+=		ext/File-DosGlob/lib/File/DosGlob.pm

# leads to test errors, shebang not necessary according to upstream
# shebang will be removed in 5.42
# https://github.com/Perl/perl5/issues/22751#issuecomment-2486616440
#REPLACE_PERL+=		cpan/version/lib/version.pm
# this file is not installed, and its checksums are in multiple places, breaking
# tests, so do not replace the shebang here.
# https://github.com/Perl/perl5/issues/22751
#REPLACE_PERL+=		lib/unicore/mktables

.if ${PKGSRC_COMPILER:Mxlc}
SUBST_CLASSES+=		cpprun
SUBST_STAGE.cpprun=	pre-install
SUBST_FILES.cpprun=	lib/Config_heavy.pl
.  if !empty(PKG_OPTIONS:Mthreads)
SUBST_SED.cpprun=	-e "s/cpprun=''/cpprun='cc_r -E'/"
.  else
SUBST_SED.cpprun=	-e "s/cpprun=''/cpprun='cc -E'/"
.  endif
.endif

# Some platforms may want the directory mode not to be 0755.  This
# is, unfortunately, hardcoded in quite a few places in Perl, so
# let's substitute what pkgsrc says instead.
#
SUBST_CLASSES+=		dirmode
SUBST_STAGE.dirmode=	pre-configure
SUBST_FILES.dirmode=	install_lib.pl
SUBST_SED.dirmode=	-e "s/755/${PKGDIRMODE}/g;/umask(/d"

post-extract:
	${CP} ${FILESDIR}/Policy.sh ${WRKSRC}/Policy.sh
.if ${USE_CROSS_COMPILE:tl} == "yes"
	cd ${WRKSRC} && ${GZIP_CMD} -dc ${_DISTDIR}/${PERL_CROSS}.tar.gz | \
		${PAX} -r -s ',^${PERL_CROSS}/,,'
.  if exists(${FILESDIR}/perl-cross-${LOWER_OPSYS}.hints)
	${CP} ${FILESDIR}/perl-cross-${LOWER_OPSYS}.hints ${WRKSRC}/cnf/hints/${LOWER_OPSYS}
.  endif
.endif

pre-configure:
	${FIND} ${WRKSRC} -name "*.orig" -type f -exec rm -f {} \;

post-build:
	${SED}	-e "s,@PERL5@,"${PERL5:Q}",g"				\
		-e "s,@SH@,"${SH:Q}",g"					\
		-e "s,@PKGMANDIR@,"${PKGMANDIR}",g"			\
		${FILESDIR}/perllink.in > ${WRKDIR}/perllink.sh

INSTALLATION_DIRS=	bin ${PKGMANDIR}/man1
PERL5_PACKLIST_DIR_cmd=	. ${WRKSRC}/config.sh;	echo $$installarchlib
PERL5_PACKLIST_DIR=	${PERL5_PACKLIST_DIR_cmd:sh}
PERL5_PACKLIST=		.packlist
PERL5_PACKLIST_DESTDIR=	no
FILES_SUBST+=		PERL5_COMMENT=\#
FILES_SUBST+=		PERL5_PACKLIST=

.PHONY: perl5-post-install
post-install: perl5-post-install
perl5-post-install:
	${RUN}if ${TEST} -x ${DESTDIR}${PREFIX}/bin/a2p; then		\
		strip ${DESTDIR}${PREFIX}/bin/a2p;			\
	fi
	${INSTALL_SCRIPT} ${WRKDIR}/perllink.sh 			\
		${DESTDIR}${PERL5_PERLBASE}/bin/perllink
	${INSTALL_MAN} ${FILESDIR}/perllink.1				\
		${DESTDIR}${PERL5_PERLBASE}/${PKGMANDIR}/man1/perllink.1
	${RM} -f ${DESTDIR}${PREFIX}/bin/perllink			\
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man1/perllink.1
	${LN} -s ${PERL5_PERLBASE}/bin/perllink 			\
		${DESTDIR}${PREFIX}/bin/perllink
	${LN} -s ${PERL5_PERLBASE}/${PKGMANDIR}/man1/perllink.1		\
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man1/perllink.1
.if ${OPSYS} == "Haiku"
	${CHMOD} a+x ${DESTDIR}${PREFIX}/bin/perl
.endif
.if ${USE_CROSS_COMPILE:tl} == "yes"
	# perl-cross's install removes the versioned name installperl made
	# (and recorded in the .packlist); a native build has it.
	${LN} -f ${DESTDIR}${PREFIX}/bin/perl \
		${DESTDIR}${PREFIX}/bin/perl${PKGVERSION_NOREV}
.endif

.include "packlist.mk"
.include "../../mk/bsd.pkg.mk"
