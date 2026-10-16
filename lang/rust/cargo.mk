# $NetBSD: cargo.mk,v 1.47 2026/06/03 09:06:11 adam Exp $
#
# Common logic that can be used by packages that depend on cargo crates
# from crates.io. This lets existing pkgsrc infrastructure fetch and verify
# cargo crates instead of using the rust package manager in the build phase.
# Inspired by cargo.mk from FreeBSD ports.
#
# Usage example:
#
# CARGO_CRATE_DEPENDS+=	sha1-0.20
# .include "../../lang/rust/cargo.mk"
#
# If modifying the list of dependencies, re-run the build once without
# --offline in CARGO_ARGS to generate a new valid Cargo.lock.
# e.g: make CARGO_ARGS="build --release" build
#
# a list of CARGO_CRATE_DEPENDS can be generated via
#      make print-cargo-depends > cargo-depends.mk
#
# See also www/geckodriver for a full example.
#
# Some dependencies are pulled in from git repositories directly (not
# using crates.io). You can define CARGO_GITHUB_CRATES for
# those. Every entry in CARGO_GITHUB_CRATES consists of three parts
# ("user", "name", "hash") separated by spaces, where "user" is the
# github user account (first part of the github URL), "name" is the
# github project name (second part of the github URL) and "hash" is
# the git revision to fetch. For example:
#
# CARGO_GITHUB_CRATES=	foo bar 12345
#
# will fetch https://github.com/foo/bar/ revision 12345
#
# Cross-compiling with RUST_CROSS_TARGET (see rust.mk), the build host's
# cargo builds for that target. CARGO_CROSS_PATCHES lists crates to take from
# local sources instead of crates.io, as name=directory or, for one of several
# versions of a crate, name@version=directory (crates ported to the target
# that crates.io's releases do not cover yet), and CARGO_CROSS_DEPENDS the
# tool dependencies that provide them. CARGO_CROSS_VENDOR_PATCHES lists
# patches for vendored crates, as name=patchfile: each is applied (-p0, in the
# crate's directory) to every vendored version of the crate that it fits.
# CARGO_CROSS_VENDOR_SED lists sed scripts, as name=scriptfile, run over the
# .rs files of every vendored version of the crate (a target added to the
# crate's lists of target_os, say).

MASTER_SITES?=	${MASTER_SITE_CRATESIO}${PKGBASE}/

CHECK_SSP_SUPPORTED=	no

.include "../../lang/rust/rust.mk"

USE_TOOLS+=		bsdtar digest
.if ${RUST_TYPE} == "cross" && !empty(CARGO_CROSS_VENDOR_PATCHES)
USE_TOOLS+=		patch
.endif
CARGO_VENDOR_DIR=	${WRKDIR}/vendor
CARGO_WRKSRC?=		${WRKSRC}

# The Cargo.lock files of a cross build: the one cargo uses for
# CARGO_WRKSRC, which is the workspace's, above it for a member (cargo-audit,
# sem), and those below it that a meson or make build runs cargo in
# (powerdns-recursor); not the vendored crates', nor tests', fixtures' or
# fuzzers'.
_CARGO_CROSS_NAMES=	${CARGO_CROSS_PATCHES:C/[@=].*//:O:u}
_CARGO_CROSS_LOCKS=	{ d=${CARGO_WRKSRC:Q};					\
	while [ "$$d" != ${WRKDIR:Q} -a "$$d" != / ]; do			\
	  [ -f "$$d/Cargo.lock" ] && { ${ECHO} "$$d/Cargo.lock"; break; };	\
	  d="$${d%/*}";							\
	done;									\
	${FIND} ${CARGO_WRKSRC:Q} -name Cargo.lock ! -path '*/vendor/*'	\
	  ! -path '*/tests/*' ! -path '*/fixtures/*' ! -path '*/fuzz/*'	\
	  ! -path '*/target/*'						\
	  -print; } | ${SORT} -u

# TODO: some Cargo.lock files include git+https sources which need to be fetched from the URL (not necessarily resolving to a crate.io url)
DISTFILES?=			${DEFAULT_DISTFILES}

.if defined(CARGO_GITHUB_CRATES)
SUBST_CLASSES+=			gitcrate
SUBST_FILES.gitcrate+=		Cargo.toml
SUBST_MESSAGE.gitcrate=		Replacing github crate path with local path.
SUBST_STAGE.gitcrate=		pre-configure
.  for user name hash in ${CARGO_GITHUB_CRATES}
DISTFILES+=			${name}-${hash}.tar.gz
SITES.${name}-${hash}.tar.gz+=	-${MASTER_SITE_GITHUB:=${user}/}${name}/archive/${hash}.tar.gz
SUBST_SED.gitcrate+=		-E -e 's!git.*github.com/${user}/${name}.*${hash}(.)!path = \1../${name}-${hash}\1!'
.  endfor
.endif

.for crate in ${CARGO_CRATE_DEPENDS}
DISTFILES+=			${crate}.crate
SITES.${crate}.crate+=		-${MASTER_SITE_CRATESIO}${crate:C/-[0-9]+\.[0-9.]+.*$//}/${crate}.crate
EXTRACT_DIR.${crate}.crate?=	${CARGO_VENDOR_DIR}
.endfor

.include "../../mk/bsd.prefs.mk"
# Triggers NetBSD ld.so bug (PR toolchain/54192)
# See Makefile for further information.
.if ${OPSYS} == "NetBSD" && ${OPSYS_VERSION} < 099957
MAKE_JOBS_SAFE=	no
.endif

post-extract: cargo-vendor-crates
.PHONY: cargo-vendor-crates
cargo-vendor-crates:
	@${STEP_MSG} "Extracting local cargo crates"
	${RUN}${MKDIR} ${WRKDIR}/.cargo
	${RUN}${PRINTF} "[source.crates-io]\nreplace-with = \"vendored-sources\"\n[source.vendored-sources]\ndirectory = \"${CARGO_VENDOR_DIR}\"\n" > ${WRKDIR}/.cargo/config.toml
	${RUN}${MKDIR} ${CARGO_VENDOR_DIR}
.if ${RUST_TYPE} == "cross" && !empty(CARGO_CROSS_PATCHES)
	${RUN}${PRINTF} "[patch.crates-io]\n" >> ${WRKDIR}/.cargo/config.toml
.  for p in ${CARGO_CROSS_PATCHES}
	${RUN}${PRINTF} '%s = { path = "%s", package = "%s" }\n'		\
	  ${p:C/=.*//:S/@/-/:S/./_/g} ${p:C/^[^=]*=//} ${p:C/[@=].*//}	\
	  >> ${WRKDIR}/.cargo/config.toml
.  endfor
# cargo keeps a locked version over a patch: drop the patched crates from
# the Cargo.lock files.
	${RUN}for l in `${_CARGO_CROSS_LOCKS}`; do				\
	  ${AWK} -v names="${_CARGO_CROSS_NAMES}" '				\
	    BEGIN { RS = ""; ORS = "\n\n"; n = split(names, a, " ") }		\
	    { for (i = 1; i <= n; i++)						\
		if (index($$0, "\nname = \"" a[i] "\"\n")) next; print }'	\
	    "$$l" > "$$l.cross" && ${MV} "$$l.cross" "$$l";			\
	done
# A crate that pins a patched crate exactly (nix 0.31: libc "=0.2.180",
# decmpfs: libc "=0.2.186") holds every user of it on the vendored,
# unpatched version, and cargo leaves the patch unused: relax such pins.
	${RUN}cd ${CARGO_VENDOR_DIR} && for f in */Cargo.toml; do		\
	  ${AWK} -v names=" ${_CARGO_CROSS_NAMES} " '				\
	    /^\[/ { dep = "" }							\
	    /^\[.*dependencies\.[^]]*\]$$/ { dep = $$0;			\
	      sub(/.*dependencies\./, "", dep); sub(/\]$$/, "", dep);		\
	      gsub(/"/, "", dep) }						\
	    dep != "" && index(names, " " dep " ") && /^version = "=/ {	\
	      sub(/"=/, "\""); c = 1 }						\
	    { print } END { exit !c }' "$$f" > "$$f.cross" &&			\
	  ${MV} "$$f.cross" "$$f" || ${RM} -f "$$f.cross";			\
	done
.endif
.if ${RUST_TYPE} == "cross"
.  for p in ${CARGO_CROSS_VENDOR_PATCHES}
	${RUN}for d in ${CARGO_VENDOR_DIR}/${p:C/=.*//}-[0-9]*; do		\
	  [ -d "$$d" ] || continue;						\
	  if { ${PATCH} -d "$$d" -p0 -s -f --dry-run < ${p:C/^[^=]*=//} ||	\
	       ${PATCH} -d "$$d" -p0 -s -f -C < ${p:C/^[^=]*=//}; }		\
	      > /dev/null 2>&1; then						\
	    ${STEP_MSG} "Applying ${p:C/^[^=]*=//:T} to $${d##*/}";		\
	    ${PATCH} -d "$$d" -p0 -s -f < ${p:C/^[^=]*=//};			\
	  fi;									\
	done
.  endfor
.  for s in ${CARGO_CROSS_VENDOR_SED}
	${RUN}for d in ${CARGO_VENDOR_DIR}/${s:C/=.*//}-[0-9]*; do		\
	  [ -d "$$d" ] || continue;						\
	  ${STEP_MSG} "Applying ${s:C/^[^=]*=//:T} to $${d##*/}";		\
	  ${FIND} "$$d" -name '*.rs' -print | while read f; do			\
	    ${SED} -f ${s:C/^[^=]*=//} "$$f" > "$$f.cross" &&			\
	    ${MV} "$$f.cross" "$$f";						\
	  done;									\
	done
.  endfor
.endif
.for crate in ${CARGO_CRATE_DEPENDS}
	${RUN}${PRINTF} '{"package":"%s","files":{}}'	\
	  `${DIGEST} sha256 < ${_DISTDIR}/${crate}.crate` \
	  > ${CARGO_VENDOR_DIR}/${crate}/.cargo-checksum.json
.endfor

.if ${RUST_TYPE} == "cross" && !empty(CARGO_CROSS_PATCHES)
# With the patched crates dropped from Cargo.lock, cargo writes them back,
# resolved to the patches, on its first run; builds that pass --locked
# (maturin, librsvg's meson wrapper: cargo cbuild --locked) refuse that.
# So resolve once here, offline, keeping every other locked version.
pre-configure: cargo-cross-lock
.PHONY: cargo-cross-lock
cargo-cross-lock:
	${RUN}for l in `${_CARGO_CROSS_LOCKS}`; do				\
	  (cd "$${l%/*}" && ${SETENV} ${MAKE_ENV} ${CARGO} metadata	\
	    --offline --format-version 1 > /dev/null) ||			\
	  ${ECHO} "cargo.mk: could not resolve the patched crates in $$l";	\
	done

# Packages install what cargo built from target/release ("do-install: ...
# target/release/foo"); built for RUST_CROSS_TARGET it is under
# target/${RUST_CROSS_TARGET}/release, and target/release holds only the
# build host's build scripts: link the products there.
post-build: cargo-cross-products
.PHONY: cargo-cross-products
cargo-cross-products:
	${RUN}d=${CARGO_WRKSRC}/target/${RUST_CROSS_TARGET}/release;		\
	[ -d "$$d" ] || exit 0;							\
	${MKDIR} ${CARGO_WRKSRC}/target/release;				\
	for f in "$$d"/*; do							\
	  [ -f "$$f" ] || continue;						\
	  t=${CARGO_WRKSRC}/target/release/`basename "$$f"`;			\
	  [ -e "$$t" ] || ${LN} "$$f" "$$t" 2>/dev/null || ${CP} -p "$$f" "$$t"; \
	done
.endif

# Legacy name
.PHONY: show-cargo-depends
show-cargo-depends: print-cargo-depends

.PHONY: print-cargo-depends
print-cargo-depends:
	${RUN}${AWK} 'BEGIN {print "# $$Net" "BSD$$"; print;}		\
		/^name = / { split($$3, a, "\""); name=a[2]; }		\
		/^version = / { split($$3, a, "\""); vers=a[2]; }	\
		/^source = / {						\
			print "CARGO_CRATE_DEPENDS+=\t" name "-" vers;	\
			}' ${CARGO_WRKSRC}/Cargo.lock

.if ${RUST_TYPE} == "native"
CARGO=			cargo
.elif ${RUST_TYPE} == "cross"
CARGO=			${TOOLBASE}/bin/cargo
.else
CARGO=			${PREFIX}/bin/cargo
.endif
DEFAULT_CARGO_ARGS=	--offline -j${_MAKE_JOBS_N}	\
			  ${CARGO_NO_DEFAULT_FEATURES:M[yY][eE][sS]:C/[yY][eE][sS]/--no-default-features/}	\
			  ${CARGO_FEATURES:C/.*/--features/W}	\
			  ${CARGO_FEATURES:S/ /,/Wg}
.if ${RUST_TYPE} == "cross"
# rust.mk sets the toolchains up for the target
DEFAULT_CARGO_ARGS+=	--target ${RUST_CROSS_TARGET}
TOOL_DEPENDS+=		${CARGO_CROSS_DEPENDS}
# openssl-sys's vendored feature (termscp) builds OpenSSL from source, which
# openssl-src cannot configure for every target: use pkgsrc's.
MAKE_ENV+=		OPENSSL_NO_VENDOR=1
.endif

CARGO_ARGS?=		build --release ${DEFAULT_CARGO_ARGS}
CARGO_INSTALL_ARGS?=	install --path . --root ${DESTDIR}${PREFIX} ${DEFAULT_CARGO_ARGS}

MAKE_ENV+=		RUSTFLAGS=${RUSTFLAGS:Q}
ALL_ENV+=		CARGO_HOME=${WRKDIR}

.if !target(do-build)
do-build: do-cargo-build
.endif

.PHONY: do-cargo-build
do-cargo-build:
	${RUN} cd ${CARGO_WRKSRC} && ${SETENV} ${MAKE_ENV} ${CARGO} ${CARGO_ARGS}

.if !target(do-install) && ${GNU_CONFIGURE:Uno:tl} == no
do-install: do-cargo-install
.endif

.PHONY: do-cargo-install
do-cargo-install:
	${RUN} cd ${CARGO_WRKSRC} && ${SETENV} ${MAKE_ENV} ${CARGO} ${CARGO_INSTALL_ARGS}
	# remove files cargo uses for tracking installations
	${RM} -f ${DESTDIR}${PREFIX}/.crates.toml
	${RM} -f ${DESTDIR}${PREFIX}/.crates2.json

.if ${OPSYS} == "Darwin"
.PHONY: do-cargo-post-install-darwin-fix-rpath
post-install: do-cargo-post-install-darwin-fix-rpath
do-cargo-post-install-darwin-fix-rpath:
	${RUN} cd ${DESTDIR};								\
	for i in $$(${FIND} .${PREFIX}/lib -name '*.so' | ${SED} -e 's|^\./||'); do	\
	  install_name_tool -id /$$i $$i;						\
	done
.endif
