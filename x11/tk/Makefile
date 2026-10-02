# $NetBSD: Makefile,v 1.98 2026/01/12 22:25:04 rillig Exp $

DISTNAME=	tk${TK_VERSION}-src
PKGNAME=	tk-${TK_VERSION}
CATEGORIES=	x11 lang
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=tcl/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://www.tcl.tk/
COMMENT=	Graphical toolkit for TCL (8.6 branch)
LICENSE=	2-clause-bsd

.include "../../x11/tk/Makefile.version"

WRKSRC=			${WRKDIR}/tk${TK_VERSION}

USE_GCC_RUNTIME=	yes

GNU_CONFIGURE=		yes
GNU_CONFIGURE_ICONV=	no
CONFIGURE_DIRS=		unix
BUILD_DIRS=		${CONFIGURE_DIRS}
CONFIGURE_ARGS+=	--with-tcl=${_CROSS_DESTDIR:U}${BUILDLINK_PREFIX.tcl}/lib
CONFIGURE_ENV+=		LIB_RUNTIME_DIR=${PREFIX}/lib
PKGCONFIG_OVERRIDE+=	unix/tk.pc.in
TEST_TARGET=		test

CHECK_PORTABILITY_SKIP=	win/configure

.if defined(ABI) && ${ABI} == "64"
CONFIGURE_ARGS+=	--enable-64bit
.endif

.include "options.mk"

# IRIX: configure links shared libraries with SGI's ld and its flags (as
# tcl's does); link them with the compiler instead.
SUBST_CLASSES.IRIX+=		irix-shlib
SUBST_STAGE.irix-shlib=		pre-configure
SUBST_MESSAGE.irix-shlib=	Linking shared libraries with the compiler.
SUBST_FILES.irix-shlib=		unix/configure
SUBST_SED.irix-shlib=		-e "s|SHLIB_LD=\"ld -n32 -shared -rdata_shared\"|SHLIB_LD='\$${CC} -shared'|"
SUBST_SED.irix-shlib+=		-e "s|LD_SEARCH_FLAGS='-rpath \$${LIB_RUNTIME_DIR}'|LD_SEARCH_FLAGS='-Wl,-rpath,\$${LIB_RUNTIME_DIR}'|"

SUBST_CLASSES+=		tk-config
SUBST_STAGE.tk-config=	post-build
SUBST_FILES.tk-config=	unix/tkConfig.sh
SUBST_SED.tk-config+=	-e "s|${WRKSRC}/unix|${PREFIX}/lib|"
SUBST_SED.tk-config+=	-e "s|${WRKSRC}|${PREFIX}/include/tk|"

PLIST_SUBST+=		SONUM=${TK_SONUM}
PLIST_SUBST+=		BASEVER=${TK_BASEVER}

.include "../../lang/tcl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
