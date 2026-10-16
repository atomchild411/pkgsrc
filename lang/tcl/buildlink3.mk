# $NetBSD: buildlink3.mk,v 1.38 2026/06/04 09:52:59 adam Exp $

BUILDLINK_TREE+=	tcl

.if !defined(TCL_BUILDLINK3_MK)
TCL_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.tcl+=	tcl>=8.5.7
BUILDLINK_ABI_DEPENDS.tcl+=	tcl>=8.6.1nb1
BUILDLINK_PKGSRCDIR.tcl?=	../../lang/tcl

BUILDLINK_FILES.tcl+=	bin/tclsh*
#
# Make "-ltcl" and "-ltcl8.6" resolve into "-ltcl86", so that we don't
# need to patch so many Makefiles.
#
BUILDLINK_TRANSFORM+=	l:tcl:tcl86
BUILDLINK_TRANSFORM+=	l:tcl8.6:tcl86

_TOOLS_USE_PKGSRC.tclsh=	yes

TCLCONFIG_SH?=		${BUILDLINK_PREFIX.tcl}/lib/tclConfig.sh
TCLSH=			${BUILDLINK_PREFIX.tcl}/bin/tclsh
# Bundled library
ITCL_VERSION=		4.3.7
TDBC_VERSION=		1.1.13

.include "../../mk/bsd.fast.prefs.mk"
.if ${OPSYS} == "IRIX"
# TEA's tcl.m4 links IRIX shared libraries with SGI's ld and its flags
# (SHLIB_LD="ld -n32 -shared -rdata_shared"); link them with the compiler,
# as lang/tcl and x11/tk do for themselves.
SUBST_CLASSES+=			tea-irix-shlib
SUBST_STAGE.tea-irix-shlib=	pre-configure
SUBST_MESSAGE.tea-irix-shlib=	Linking TEA shared libraries with the compiler.
SUBST_FILES.tea-irix-shlib=	configure */configure */*/configure
SUBST_FILES.tea-irix-shlib+=	aclocal.m4 tcl.m4 */tcl.m4	# for autoreconf
SUBST_SED.tea-irix-shlib=	-e "s|SHLIB_LD=\"ld -n32 -shared -rdata_shared\"|SHLIB_LD='\$${CC} -shared'|"
SUBST_SED.tea-irix-shlib+=	-e "s|LD_SEARCH_FLAGS='-rpath \$${LIB_RUNTIME_DIR}'|LD_SEARCH_FLAGS='-Wl,-rpath,\$${LIB_RUNTIME_DIR}'|"
SUBST_NOOP_OK.tea-irix-shlib=	yes
.endif

.include "../../devel/zlib/buildlink3.mk"
.include "../../mk/dlopen.buildlink3.mk"
.endif # TCL_BUILDLINK3_MK

BUILDLINK_TREE+=	-tcl
