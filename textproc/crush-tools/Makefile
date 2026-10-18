# $NetBSD: Makefile,v 1.14 2022/06/28 11:36:09 wiz Exp $

DISTNAME=	crush-tools-2013-04
PKGNAME=	${DISTNAME:C/-([0-9]+)$/.\1/}
PKGREVISION=	9
CATEGORIES=	textproc
MASTER_SITES=	http://crush-tools.googlecode.com/files/

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/google/crush-tools
COMMENT=	Collection of tools for processing delimited-text data
LICENSE=	apache-2.0

DEPENDS+=	p5-DBI-[0-9]*:../../databases/p5-DBI
DEPENDS+=	p5-Date-Calc-[0-9]*:../../devel/p5-Date-Calc
#DEPENDS+=	{perl>=5,p5-Getopt-Long-[0-9]*}:../../devel/p5-Getopt-Long

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes
USE_TOOLS+=	gm4 gmake perl

REPLACE_PERL+=	src/bin/genman.pl

CFLAGS.SunOS+=	-Du_int32_t=uint32_t

.include "../../mk/bsd.prefs.mk"

.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# configure looks for Date::Calc in the build host's perl; the scripts that
# need it get it from DEPENDS on the target.
SUBST_CLASSES+=		datecalc
SUBST_STAGE.datecalc=	pre-configure
SUBST_MESSAGE.datecalc=	Taking Date::Calc from DEPENDS.
SUBST_FILES.datecalc=	configure
SUBST_SED.datecalc=	-e 's,^  \$$PERL -MDate::Calc -e exit >/dev/null 2>&1$$,  true,'
.endif

.include "../../devel/pcre/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
