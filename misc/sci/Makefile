# $NetBSD: Makefile,v 1.17 2017/09/04 18:00:57 wiz Exp $
#

DISTNAME=	sci-0.5.6
PKGREVISION=	2
CATEGORIES=	misc
MASTER_SITES=	http://linuxparts.com/

MAINTAINER=	pkgsrc-users@NetBSD.org
#HOMEPAGE=	http://linuxparts.com/software.html
COMMENT=	Curses based data entry via templates

GNU_CONFIGURE=	yes

INSTALLATION_DIRS+=	share/doc/sci share/examples/sci

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# keys.x is made from the curses header, looked for in /usr/include: use
# the target's (pkgsrc ncurses) instead of the build machine's.
SUBST_CLASSES+=		cursesh
SUBST_STAGE.cursesh=	pre-configure
SUBST_FILES.cursesh=	Makefile.in
SUBST_SED.cursesh=	-e 's,CURSESH="/usr/include/ncurses\.h",CURSESH="${BUILDLINK_DIR}/include/ncurses/ncurses.h",'
SUBST_MESSAGE.cursesh=	Making keys.x from the target's curses header.
.endif

post-install:
	for i in COPYING README INSTALL NEWS ; do \
		${INSTALL_DATA} ${WRKSRC}/$$i ${DESTDIR}${PREFIX}/share/doc/sci ; \
	   done
	for i in samples/* ; do \
		${INSTALL_DATA} ${WRKSRC}/$$i ${DESTDIR}${PREFIX}/share/examples/sci ; \
	   done

.include "../../mk/curses.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
