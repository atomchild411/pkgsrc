# $NetBSD: module.mk,v 1.1 2022/03/08 00:09:30 wiz Exp $
#
# Common build logic for Guile 3.0 modules using gnu configure.
#
# === Package-settable-variables ===
#
# GUILE_NEED_BOOTSTRAP
#	Whether the package requires a bootstrap run of autotools
# 	or not.
#
#	Possible values: yes no

.if defined(GNU_CONFIGURE)
GNU_CONFIGURE_PREFIX=	${PREFIX}/guile/3.0
CONFIGURE_ARGS+=	--libdir=${PREFIX}/guile/3.0/lib

.  include "../../mk/bsd.fast.prefs.mk"
.  if ${USE_CROSS_COMPILE:U:tl} == "yes"
# The Scheme is compiled by the build machine's guild, for the target
# (configure's GUILE_TARGET). Guile knows "mips", not "mipseb".
TOOL_DEPENDS+=		guile30>=3.0:../../lang/guile30
CONFIGURE_ENV+=		GUILE=${TOOLBASE}/guile/3.0/bin/guile
CONFIGURE_ENV+=		GUILD=${TOOLBASE}/guile/3.0/bin/guild
MAKE_FLAGS+=		GUILE_TARGET=--target=${MACHINE_GNU_PLATFORM:S/^mipseb-/mips-/}
# Guile modules this one uses are installed for the target: let the build
# machine's guile load their source (their .go files are the target's).
_GUILE_CROSS_ENV=	GUILE_LOAD_PATH=${CROSS_DESTDIR}${LOCALBASE}/guile/3.0/share/guile/site/3.0
_GUILE_CROSS_ENV+=	GUILE_AUTO_COMPILE=0
CONFIGURE_ENV+=		${_GUILE_CROSS_ENV}
MAKE_ENV+=		${_GUILE_CROSS_ENV}
.  endif

.  if defined(GUILE_NEED_BOOTSTRAP)
USE_TOOLS+=		automake autoconf autoreconf
pre-configure:
	(cd ${WRKSRC} && ${SETENV} ${CONFIGURE_ENV} autoreconf -I${TOOLBASE}/guile/3.0/share/aclocal -vif)
.  endif

.include "../../lang/guile30/buildlink3.mk"
.endif
