# $NetBSD: Makefile,v 1.93 2026/09/02 19:04:22 wiz Exp $

PKGNAME=		amanda-common-${AMANDA_VERSION}
PKGREVISION=		16

COMMENT=		Common libraries and binaries for Amanda

# genversion.c:37:10: fatal error: 'genversion.h' file not found
MAKE_JOBS_SAFE=		no

.include "../../sysutils/amanda-common/Makefile.common"

CPPFLAGS.SunOS+=	-D_LARGEFILE64_SOURCE
LDFLAGS.SunOS+=		-lsocket

CONFIGURE_ARGS+=	--without-server --without-client --without-gnuplot

PKG_GROUPS=		${AMANDA_GROUP}
PKG_USERS=		${AMANDA_USER}:${AMANDA_GROUP}

PKG_GECOS.${AMANDA_USER}=	Amanda backup user
PKG_SHELL.${AMANDA_USER}=	${SH}
PKG_HOME.${AMANDA_USER}=	${AMANDA_VAR}

OWN_DIRS+=		${PKG_SYSCONFDIR}/amanda
OWN_DIRS_PERMS=		${AMANDA_VAR} ${AMANDA_USER} ${AMANDA_GROUP} 0750
OWN_DIRS_PERMS+=	${AMANDA_VAR}/gnutar-lists ${AMANDA_USER} ${AMANDA_GROUP} 0750
OWN_DIRS_PERMS+=	${VARBASE}/log/amanda ${AMANDA_USER} ${AMANDA_GROUP} 0750

CONF_FILES_PERMS=	${PREFIX}/share/doc/amanda/example/amanda-client.conf \
			${PKG_SYSCONFDIR}/amanda/amanda-client.conf     \
			${AMANDA_USER} ${AMANDA_GROUP} 0600
CONF_FILES_PERMS=	${PREFIX}/share/doc/amanda/example/amanda-security.conf \
			${PKG_SYSCONFDIR}/amanda/amanda-security.conf     \
			root ${AMANDA_GROUP} 0640

REQD_FILES_PERMS+=	/dev/null ${AMANDA_VAR}/amandates ${AMANDA_USER} ${AMANDA_GROUP} 0640

SPECIAL_PERMS+=		sbin/amservice ${AM_PROG_PERMS}

# genversion writes version.c (the build settings "amadmin version" shows),
# and make_security_file amanda-security.conf; both are built for IRIX.
# Cross-compiling: a short version.c, and make_security_file (stdio and
# config.h only, not amanda.h and GLib) built for the build host.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
SUBST_CLASSES+=			genversion
SUBST_STAGE.genversion=		pre-configure
SUBST_MESSAGE.genversion=	version.c without running genversion.
SUBST_FILES.genversion=		common-src/Makefile.in
SUBST_SED.genversion=		-e 's|\./genversion$$(EXEEXT) > version\.c|cp ${WRKDIR}/version-cross.c version.c|'
SUBST_SED.genversion+=		-e 's|^	\./make_security_file$$|	${WRKDIR}/make_security_file-native|'
post-configure: amanda-cross-version
.PHONY: amanda-cross-version
amanda-cross-version:
	printf '%s\n' '/* version.c - cross-compiled: not from genversion */' \
	    'const char * const version_info[] = {' \
	    '  "  build: VERSION=\"Amanda-${AMANDA_VERSION}\"\n",' \
	    '  0' '};' > ${WRKDIR}/version-cross.c
	sed 's|^#include <amanda.h>|#include "config.h"\n#include <stdio.h>\n#include <stdlib.h>|' \
	    ${WRKSRC}/common-src/make_security_file.c > ${WRKDIR}/msf.c
	${NATIVE_CC} -I${WRKSRC}/config -o ${WRKDIR}/make_security_file-native \
	    ${WRKDIR}/msf.c
.endif

.include "../../mk/bsd.pkg.mk"
