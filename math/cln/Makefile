# $NetBSD: Makefile,v 1.31 2025/07/18 16:19:44 schmonz Exp $

DISTNAME=	cln-1.3.7
CATEGORIES=	math
MASTER_SITES=	${HOMEPAGE}
MASTER_SITES+=	ftp://ftpthep.physik.uni-mainz.de/pub/gnu/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	adam@NetBSD.org
HOMEPAGE=	https://www.ginac.de/CLN/
COMMENT=	Class Library for Numbers
LICENSE=	gnu-gpl-v2

USE_TOOLS+=		gmake pkg-config
USE_LANGUAGES=		c c++
USE_LIBTOOL=		yes
GNU_CONFIGURE=		yes
PKGCONFIG_OVERRIDE=	cln.pc.in
INFO_FILES=		yes
TEST_TARGET=		check

# Work around broken configure test
CONFIGURE_ENV.SunOS+=	cl_cv_proto_perror=yes
# The MIPS assembly is written for GNU as (two-operand nor, ...), which
# LLVM's assembler does not take: use the C versions.
CPPFLAGS.IRIX+=		-DNO_ASM

.include "../../mk/bsd.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# Cross-compiling, configure finds an integer type's width by doubling (type)2
# until it wraps to 0. Clang takes the overflowing bound for a variable-length
# array, so the probe passes one doubling early: int 31 bits, long long 63.
SUBST_CLASSES+=		intparam
SUBST_STAGE.intparam=	post-configure
SUBST_MESSAGE.intparam=	Correcting the signed integer widths.
SUBST_FILES.intparam=	include/cln/intparam.h
SUBST_SED.intparam=	-e 's/bitsize 31$$/bitsize 32/'
SUBST_SED.intparam+=	-e 's/bitsize 63$$/bitsize 64/'
SUBST_SED.intparam+=	-e '/different sizes!!/d'
.endif

.include "../../devel/gmp/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
