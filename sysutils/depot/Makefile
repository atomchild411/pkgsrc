# $NetBSD: Makefile,v 1.25 2021/04/21 08:53:30 wiz Exp $

DISTNAME=	depot-5.14
CATEGORIES=	sysutils
MASTER_SITES=	# ftp://ftp.andrew.cmu.edu/pub/depot/alpha/

MAINTAINER=	pkgsrc-users@NetBSD.org
# "Most of the content here is being removed and archived."
# HOMEPAGE=	http://asg.web.cmu.edu/depot/
COMMENT=	Maps several separate packages into a tree without merging them

MAKE_JOBS_SAFE=	no

GNU_CONFIGURE=	yes
USE_TOOLS+=	lex yacc

CONFIGURE_ENV+=	INSTALL="" CC=${CC:Q}
MAKE_ENV+=	CC=${CC:Q}

INSTALLATION_DIRS=	bin ${PKGMANDIR}/man1 ${PKGMANDIR}/man5

INSTALL_DIRS=		src/cmd man/man1 man/man5
INSTALL_MAKE_FLAGS+=	BINDIR=${DESTDIR}${PREFIX}/bin
INSTALL_MAKE_FLAGS+=	MANDIR=${DESTDIR}${PREFIX}/${PKGMANDIR}

# Its own libutil.a by path: the IRIX compiler drops -lutil from links.
SUBST_CLASSES+=		libutil
SUBST_STAGE.libutil=	pre-configure
SUBST_MESSAGE.libutil=	Linking depot's own libutil.a by path.
SUBST_FILES.libutil=	src/cmd/depot_collectioninfo/Makefile.in src/cmd/hintservice/Makefile.in
SUBST_SED.libutil=	-e 's,-lutil,../../lib/build-lib/libutil.a,'

.include "../../mk/bsd.pkg.mk"
