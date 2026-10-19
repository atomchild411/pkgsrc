# $NetBSD: Makefile,v 1.50 2026/09/02 19:03:14 wiz Exp $

DISTNAME=	ucblogo-6.2.1
PKGREVISION=	18
CATEGORIES=	lang
MASTER_SITES=	${MASTER_SITE_GITHUB:=jrincayc/}
GITHUB_PROJECT=	ucblogo-code
GITHUB_RELEASE=	version_${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://people.eecs.berkeley.edu/~bh/logo.html
COMMENT=	UCB (Berkeley) Logo interpreter
LICENSE=	gnu-gpl-v3

USE_LANGUAGES+=		c c++

GNU_CONFIGURE=		yes

# Enable object oriented Logo features
CONFIGURE_ARGS+=	--enable-objects

USE_TOOLS+=		gmake makeinfo
INFO_FILES=		yes

CFLAGS+=	-Wno-incompatible-pointer-types

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# makehelp, run at build time to split the manual into helpfiles/, is for
# the build host.
SUBST_CLASSES+=		makehelp
SUBST_STAGE.makehelp=	pre-configure
SUBST_FILES.makehelp=	Makefile.in
SUBST_SED.makehelp=	-e 's|^regenerate-help-index: makehelp usermanual$$|makehelp: makehelp.c\n	${NATIVE_CC} -I. -o makehelp makehelp.c\n\n&|'
.endif

.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../x11/wxGTK30/buildlink3.mk"
.include "../../mk/termcap.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
