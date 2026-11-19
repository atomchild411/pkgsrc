# $NetBSD$

DISTNAME=	hollidance-models-1.6
CATEGORIES=	benchmarks graphics
MASTER_SITES=	http://www.cool3dworld.org/HolliDance/
DIST_SUBDIR=	hollidance
DISTFILES=	HolliHModel.zip PennyModel.zip ReneeModel.zip SusanModel.zip
DISTFILES+=	LargeModels.zip LargeHolliHModel.zip LargePennyModel.zip
DISTFILES+=	LargeReneeModel.zip LargeSusanModel.zip

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.cool3dworld.org/HolliDance/dance.html
COMMENT=	Holli Dance 1.6 dancers, outfit and large models
LICENSE=	hollidance-license

RESTRICTED=		No commercial distribution
NO_BIN_ON_CDROM=	${RESTRICTED}
NO_SRC_ON_CDROM=	${RESTRICTED}

DEPENDS+=	hollidance>=1.6:../../benchmarks/hollidance

ONLY_FOR_PLATFORM=	IRIX-*-*
WRKSRC=			${WRKDIR}
NO_CONFIGURE=		yes
NO_BUILD=		yes

INSTALLATION_DIRS=	lib/hollidance/models

# Each kit in its own directory (they all have a Readme.txt); the hollidance
# command links their models in. LargeModels.zip unpacks as Models/.
KITS=	HolliHModel PennyModel ReneeModel SusanModel LargeHolliHModel
KITS+=	LargePennyModel LargeReneeModel LargeSusanModel

do-install:
.for k in ${KITS}
	${INSTALL_DATA_DIR} ${DESTDIR}${PREFIX}/lib/hollidance/models/${k}
	${INSTALL_DATA} ${WRKSRC}/${k}/* ${DESTDIR}${PREFIX}/lib/hollidance/models/${k}
.endfor
	${INSTALL_DATA_DIR} ${DESTDIR}${PREFIX}/lib/hollidance/models/LargeModels
	${INSTALL_DATA} ${WRKSRC}/Models/* \
	    ${DESTDIR}${PREFIX}/lib/hollidance/models/LargeModels

.include "../../mk/bsd.pkg.mk"
