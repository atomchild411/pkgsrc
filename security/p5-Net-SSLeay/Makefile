# $NetBSD: Makefile,v 1.108 2026/07/16 19:04:50 wiz Exp $

DISTNAME=	Net-SSLeay-1.96
PKGNAME=	p5-${DISTNAME}
PKGREVISION=	2
CATEGORIES=	security perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=../../authors/id/C/CH/CHRISN/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://metacpan.org/release/Net-SSLeay
COMMENT=	Perl5 module for using OpenSSL
LICENSE=	openssl

TEST_DEPENDS+=	p5-Test-Exception-[0-9]*:../../devel/p5-Test-Exception
TEST_DEPENDS+=	p5-Test-Warn-[0-9]*:../../devel/p5-Test-Warn
TEST_DEPENDS+=	p5-Test-NoWarnings-[0-9]*:../../devel/p5-Test-NoWarnings

PERL5_PACKLIST=		auto/Net/SSLeay/.packlist
.include "../../mk/bsd.prefs.mk"
# Cross builds: Makefile.PL looks for the headers and libraries under the
# prefix, which the build host has under the buildlink directory only.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
MAKE_ENV+=		OPENSSL_PREFIX=${BUILDLINK_DIR}
# Makefile.PL runs ${OPENSSL_PREFIX}/bin/openssl to read OpenSSL's version:
# the build host's (the same pkgsrc OpenSSL, as a tool), not the target's,
# which the build host cannot run.
TOOL_DEPENDS+=		openssl-[0-9]*:../../security/openssl
pre-configure: net-ssleay-host-openssl
.PHONY: net-ssleay-host-openssl
net-ssleay-host-openssl:
	${MKDIR} ${BUILDLINK_DIR}/bin
	${LN} -sf ${TOOLBASE}/bin/openssl ${BUILDLINK_DIR}/bin/openssl
.else
MAKE_ENV+=		OPENSSL_PREFIX=${SSLBASE}
.endif
MAKE_ENV+=		PERL_MM_USE_DEFAULT=1	# avoid network question
MAKE_ENV+=		DYLD_LIBRARY_PATH=${PREFIX}/lib # build on Mac OS X

.include "../../devel/zlib/buildlink3.mk"
.include "../../lang/perl5/module.mk"
.include "../../security/openssl/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
