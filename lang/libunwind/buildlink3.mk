# $NetBSD: buildlink3.mk,v 1.18 2026/04/16 06:33:52 wiz Exp $

.include "../../mk/bsd.fast.prefs.mk"

.if ${OPSYS} == "IRIX"
# IRIX: libunwind is the clang toolchain's own, which the compiler links
# by itself; IRIX machines get it from clang-irix-libs (which conflicts
# with this package), as C++ programs do.
.  if !defined(LIBUNWIND_BUILDLINK3_MK)
LIBUNWIND_BUILDLINK3_MK:=
DEPENDS+=	clang-irix-libs>=21.1.8:../../lang/clang-irix-libs
.  endif
.else
BUILDLINK_TREE+=	libunwind

.if !defined(LIBUNWIND_BUILDLINK3_MK)
LIBUNWIND_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.libunwind+=	libunwind>=21.1.0
BUILDLINK_PKGSRCDIR.libunwind?=		../../lang/libunwind

.endif	# LIBUNWIND_BUILDLINK3_MK

BUILDLINK_TREE+=	-libunwind
.endif
