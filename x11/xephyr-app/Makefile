# $NetBSD$
#
# xephyr-app and fillwm.  Both are small enough to live in files/: nothing
# is fetched, and fillwm is compiled here.

DISTNAME=	xephyr-app-20260930
CATEGORIES=	x11
MASTER_SITES=	# none
DISTFILES=	# none

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/atomchild411/pkgsrc
COMMENT=	Run newer X programs on IRIX, each in its own Xephyr window
LICENSE=	modified-bsd

ONLY_FOR_PLATFORM=	IRIX-*-*
NO_CONFIGURE=		yes
WRKSRC=			${WRKDIR}
INSTALLATION_DIRS=	bin

DEPENDS+=	modular-xorg-xephyr>=21.1.24nb2:../../x11/modular-xorg-xephyr
DEPENDS+=	xkbcomp-[0-9]*:../../x11/xkbcomp
DEPENDS+=	xkeyboard-config-[0-9]*:../../x11/xkeyboard-config

SUBST_CLASSES+=		prefix
SUBST_STAGE.prefix=	pre-build
SUBST_MESSAGE.prefix=	Setting PREFIX in xephyr-app.
SUBST_FILES.prefix=	xephyr-app
SUBST_VARS.prefix=	PREFIX

do-extract:
	${CP} ${FILESDIR}/fillwm.c ${FILESDIR}/xephyr-app ${WRKSRC}/

do-build:
	cd ${WRKSRC} && ${CC} ${CFLAGS} ${LDFLAGS} -o fillwm fillwm.c -lX11

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/fillwm ${DESTDIR}${PREFIX}/bin/
	${INSTALL_SCRIPT} ${WRKSRC}/xephyr-app ${DESTDIR}${PREFIX}/bin/

.include "../../x11/libX11/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
