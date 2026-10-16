# $NetBSD: Makefile,v 1.3 2022/08/28 18:34:15 he Exp $
#

DISTNAME=	fplll-5.3.2
CATEGORIES=	math
MASTER_SITES=	${MASTER_SITE_GITHUB:=fplll/}
GITHUB_PROJECT=	${DISTNAME:S/-${PKGVERSION}//}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://perso.ens-lyon.fr/damien.stehle/\#software
COMMENT=	Lattice algorithms using floating-point arithmetic
LICENSE=	gnu-lgpl-v2.1

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes
USE_TOOLS+=	gmake autoconf automake
USE_LANGUAGES=	c c++

TEST_TARGET=	check

pre-configure:
	cd ${WRKSRC} && ./autogen.sh

# IRIX's <ctype.h> defines _A (and _U, _L, ...): rename the member.
SUBST_CLASSES+=		ctype
SUBST_STAGE.ctype=	pre-configure
SUBST_MESSAGE.ctype=	Renaming _A, a <ctype.h> macro on some systems.
SUBST_FILES.ctype=	fplll/enum-parallel/enumeration.h
SUBST_SED.ctype=	-e 's/\<_A\>/_bound_A/g'

.include "../../mk/atomic64.mk"
.include "../../devel/gmp/buildlink3.mk"
BUILDLINK_API_DEPENDS.mpfr+=	mpfr>=2.0.3
.include "../../math/mpfr/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
