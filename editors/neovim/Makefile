# $NetBSD: Makefile,v 1.30 2026/08/27 07:48:41 adam Exp $

DISTNAME=	neovim-0.12.5
CATEGORIES=	editors
MASTER_SITES=	${MASTER_SITE_GITHUB:=neovim/}
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://neovim.io/
COMMENT=	Vim fork focused on extensibility and usability
LICENSE=	apache-2.0 AND vim-license

USE_LANGUAGES=	c c++
USE_TOOLS+=	pkg-config gettext

.include "../../mk/bsd.prefs.mk"

PLIST_VARS+=	desktop
.if ${OPSYS} != "Darwin"
PLIST.desktop=	yes
.endif

PRINT_PLIST_AWK+=	{ gsub(/^share\/applications\/nvim\.desktop$$/, "$${PLIST.desktop}&"); }

CMAKE_CONFIGURE_ARGS+=	-DCMAKE_BUILD_TYPE=Release
CMAKE_CONFIGURE_ARGS+=	-DENABLE_TRANSLATIONS=ON
CMAKE_CONFIGURE_ARGS+=	-DUSE_BUNDLED=OFF

LDFLAGS.SunOS+=		-lrt

# should follow the LuaJIT API compatibility
LUA_VERSIONS_ACCEPTED=	51

PLIST_VARS+=	nls
.if ${OPSYS} == "IRIX"
# No NLS; and nothing provides the stack protector's __stack_chk_* symbols.
CMAKE_CONFIGURE_ARGS+=	-DENABLE_TRANSLATIONS=OFF
CMAKE_CONFIGURE_ARGS+=	-DHAS_FSTACK_PROTECTOR_STRONG_FLAG=OFF
CMAKE_CONFIGURE_ARGS+=	-DHAS_FSTACK_PROTECTOR_FLAG=OFF
.else
PLIST.nls=	yes
.endif

# A cross build runs neovim's code generators and its help-tags step on the
# build host: a host Lua 5.1 with nlua0 (neovim's mpack and bit modules and
# lpeg, compiled here for the host) for the generators, and a host neovim
# for the help tags.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
TOOL_DEPENDS+=		lua51-[0-9]*:../../lang/lua51
TOOL_DEPENDS+=		neovim-[0-9]*:../../editors/neovim
LPEG_DISTNAME=		lpeg-1.1.0
DISTFILES=		${DEFAULT_DISTFILES} ${LPEG_DISTNAME}.tar.gz
SITES.${LPEG_DISTNAME}.tar.gz=	https://www.inf.puc-rio.br/~roberto/lpeg/
HOST_NLUA0=		${WRKDIR}/host-nlua0/nlua0.so
CMAKE_CONFIGURE_ARGS+=	-DLUA_GEN_PRG=${TOOLBASE}/bin/lua5.1
CMAKE_CONFIGURE_ARGS+=	-DNLUA0_HOST_PRG=${HOST_NLUA0}
CMAKE_CONFIGURE_ARGS+=	-DNVIM_HOST_PRG=${TOOLBASE}/bin/nvim
# The host Lua's bytecode is not the target's (byte order, sizes): embed
# the built-in Lua modules as source.
CMAKE_CONFIGURE_ARGS+=	-DCOMPILE_LUA=OFF
.  if ${NATIVE_OPSYS} == "Darwin"
HOST_NLUA0_LDFLAGS=	-bundle -undefined dynamic_lookup
.  else
HOST_NLUA0_LDFLAGS=	-shared
.  endif

pre-configure:
	${MKDIR} ${WRKDIR}/host-nlua0
	cd ${WRKDIR}/host-nlua0 && ${NATIVE_CC} -O2 -fPIC -DNVIM_NLUA0	\
	    -I${TOOLBASE}/include/lua-5.1 -I${WRKSRC}/src		\
	    -I${WRKDIR}/${LPEG_DISTNAME} ${HOST_NLUA0_LDFLAGS}		\
	    -o ${HOST_NLUA0} ${WRKSRC}/src/nlua0.c ${WRKSRC}/src/bit.c	\
	    ${WRKSRC}/src/mpack/*.c ${WRKDIR}/${LPEG_DISTNAME}/lp*.c
.endif

# https://github.com/neovim/neovim/issues/223#issuecomment-374763255
FORTIFY_SUPPORTED=	no

.include "../../lang/lua/luaversion.mk"

DEPENDS+=	${LUA_PKGPREFIX}-BitOp-[0-9]*:../../devel/lua-BitOp
DEPENDS+=	${LUA_PKGPREFIX}-filesystem-[0-9]*:../../devel/lua-filesystem
DEPENDS+=	${LUA_PKGPREFIX}-inspect-[0-9]*:../../devel/lua-inspect
DEPENDS+=	${LUA_PKGPREFIX}-mpack-[0-9]*:../../devel/lua-mpack

.if ${SHLIB_TYPE} == "ELF"
CFLAGS+=	${COMPILER_RPATH_FLAG}${PREFIX}/lib/lua/5.1

.  if ${OPSYS} != "IRIX"
TOOL_DEPENDS+=	patchelf-[0-9]*:../../devel/patchelf
.  endif
.endif

post-install:
	${FIND} ${DESTDIR}${PREFIX}/share/nvim/runtime -name "*.orig" -exec ${RM} -f {} +
# (IRIX: lua-lpeg's lpeg.so has a SONAME there, so nvim names it plainly.)
.if ${SHLIB_TYPE} == "ELF" && ${OPSYS} != "IRIX"
	${TOOLBASE}/bin/patchelf ${DESTDIR}${PREFIX}/bin/nvim \
		--replace-needed ${BUILDLINK_DIR.lua-lpeg}/lib/lua/5.1/lpeg.so lpeg.so
.endif

.include "../../converters/libiconv/buildlink3.mk"
.include "../../converters/utf8proc/buildlink3.mk"
.include "../../devel/cmake/build.mk"
.include "../../devel/gettext-lib/buildlink3.mk"
.if ${OPSYS} == "SunOS"
.  include "../../devel/libexecinfo/buildlink3.mk"
.endif
.include "../../devel/libuv/buildlink3.mk"
.include "../../devel/lua-lpeg/buildlink3.mk"
.include "../../devel/lua-luv/buildlink3.mk"
.include "../../devel/unibilium/buildlink3.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../lang/lua/luaversion.mk"
.include "../../lang/LuaJIT2/platform.mk"
.if ${PLATFORM_SUPPORTS_LUAJIT:tl} == "yes"
BUILDLINK_API_DEPENDS.LuaJIT2+=	LuaJIT2>=2.1
.  include "../../lang/LuaJIT2/buildlink3.mk"
.else
CMAKE_CONFIGURE_ARGS+=	-DPREFER_LUA=ON
.  include "../../lang/lua/buildlink3.mk"
.endif
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.include "../../textproc/tree-sitter/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
