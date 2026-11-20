# $NetBSD: Makefile,v 1.26 2026/05/12 16:09:35 gdt Exp $

DISTNAME=	lcms2-2.19.1
PKGREVISION=	1
CATEGORIES=	graphics
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=lcms/}

MAINTAINER=	gdt@NetBSD.org
HOMEPAGE=	http://www.littlecms.com/
COMMENT=	Little Color Management System - a color management library
LICENSE=	mit

# Upstream added cmake support in 2.19, but that has not been declared
# official/favored.  Pending upstream commentary (requested 20260430)
# or some compelling reason, the package will remain on autoconf,
# because the of the usual pattern of cmake build systems having
# regressions from autoconf in various areas, typically cross
# compilation and testing non-installed versions, at least until those
# are assessed.
USE_LIBTOOL=		yes
GNU_CONFIGURE=		yes
PKGCONFIG_OVERRIDE=	lcms2.pc.in
TEST_TARGET=		check

# IRIX (n32): pointers are 4 bytes, but doubles need 8-byte alignment. lcms2
# aligns its sub-allocations (a context's plugin data, among others) to the
# pointer size unless told otherwise, so a double read from them faults on
# IRIX (ghostscript died with a Bus error in cmsCreateTransform). The header's
# own setting for this, as on SPARC.
CPPFLAGS.IRIX+=		-DCMS_PTR_ALIGNMENT=8

# Don't switch to cmake yet as upstream has no declared it to be the
# official build system.
#.include "../../devel/cmake/build.mk"

# lcms does not need zlib, but will look for it and link it to tifficc
# if present.  Therefore, we don't enjoin lcms from finding zlib, but
# don't include it via bl3.

.include "../../graphics/tiff/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
