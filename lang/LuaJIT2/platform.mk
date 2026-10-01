# $NetBSD: platform.mk,v 1.2 2024/08/17 15:20:21 bsiegert Exp $

.include "../../mk/bsd.fast.prefs.mk"

.if !defined(PLATFORM_SUPPORTS_LUAJIT)

.  for _luajit_arch in aarch64* *arm* i386 mips* powerpc x86_64
LUAJIT_PLATFORMS+=		*-*-${_luajit_arch}
.  endfor

.  for _luajit_platform in ${LUAJIT_PLATFORMS}
# (LuaJIT's MIPS ports are o32 and n64; IRIX userland is n32.)
.    if !empty(MACHINE_PLATFORM:M${_luajit_platform}) && ${OPSYS} != "IRIX"
PLATFORM_SUPPORTS_LUAJIT=	yes
.    endif
.  endfor
PLATFORM_SUPPORTS_LUAJIT?=	no

.endif # !defined(PLATFORM_SUPPORTS_LUAJIT)
