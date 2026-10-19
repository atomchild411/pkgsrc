# $NetBSD: Makefile,v 1.9 2021/05/15 11:55:45 nia Exp $

DISTNAME=	phone-2.0
PKGREVISION=	4
CATEGORIES=	chat
MASTER_SITES=	ftp://ftp.astron.com/pub/phone/
DIST_SUBDIR=	phone-2.0nb1

MAINTAINER=	christos@NetBSD.org
HOMEPAGE=	ftp://ftp.astron.com/pub/phone/
COMMENT=	Multi-person chat program, like VMS phone
LICENSE=	generic-nonlicense

INSTALLATION_DIRS=	bin libexec ${PKGMANDIR}/man1 sbin

# needs utmpx unless someone wants to patch legacy utmp support in
BROKEN_ON_PLATFORM=	OpenBSD-*-*

BUILDLINK_TRANSFORM.Darwin+=	rm:-Wa,--fatal-warnings
CFLAGS.Darwin+=			-DINFTIM=-1

post-install:
	${INSTALL_MAN} ${WRKSRC}/phone.1 \
		${DESTDIR}${PREFIX}/${PKGMANDIR}/man1/phone.1

# The makefiles name headers under /usr/include as dependencies; a cross
# build host need not have them there (make then tries RCS co).
SUBST_CLASSES+=		incdeps
SUBST_STAGE.incdeps=	post-patch
SUBST_MESSAGE.incdeps=	Removing dependencies on /usr/include headers.
SUBST_FILES.incdeps=	master/Makefile conv/Makefile
SUBST_SED.incdeps=	-e 's,/usr/include/[a-z/]*\.h,,g'

# IRIX: the termcap functions are in ncurses (no libtermlib).
BUILDLINK_TRANSFORM.IRIX+=	rm:-ltermlib

.include "../../mk/curses.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
