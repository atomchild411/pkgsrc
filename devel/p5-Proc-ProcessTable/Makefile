# $NetBSD: Makefile,v 1.40 2026/07/16 19:03:12 wiz Exp $

DISTNAME=		Proc-ProcessTable-0.637
PKGNAME=		p5-${DISTNAME}
PKGREVISION=		1
CATEGORIES=		devel perl5
MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Proc/}

MAINTAINER=		pkgsrc-users@NetBSD.org
HOMEPAGE=		https://metacpan.org/release/Proc-ProcessTable
COMMENT=		Perl extension to access the UNIX process table
LICENSE=		${PERL5_LICENSE}

PERL5_PACKLIST=		auto/Proc/ProcessTable/.packlist

CFLAGS.SunOS+=		-D_POSIX_PTHREAD_SEMANTICS

# A cross build's MakeMaker loads the build machine's hints (perl's $^O is
# linux there), which pick os/Linux.c (glibc's obstack). Use os/IRIX.c,
# for IRIX 6.5 (hints/irix.pl would take the version from uname -r).
.include "../../mk/bsd.fast.prefs.mk"
.if ${OPSYS} == "IRIX" && ${USE_CROSS_COMPILE:U:tl} == "yes"
pre-configure: proctable-irix-hints
.PHONY: proctable-irix-hints
proctable-irix-hints:
	${PRINTF} 'symlink "os/IRIX.c", "OS.c" || die "Could not link os/IRIX.c to OS.c\\n";\n$$self->{DEFINE} = "-DIRIX_VERSION=0x006005";\n' \
		> ${WRKSRC}/hints/linux.pl
.endif

.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"
