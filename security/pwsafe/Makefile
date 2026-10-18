# $NetBSD: Makefile,v 1.23 2026/01/23 05:48:47 wiz Exp $

DISTNAME=		pwsafe-0.2.0
PKGREVISION=		11
CATEGORIES=		security
MASTER_SITES=		#

MAINTAINER=		mishka@NetBSD.org
#HOMEPAGE=		http://nsd.dyndns.org/pwsafe/
COMMENT=		CLI based PasswordSafe compatible password manager

GNU_CONFIGURE=		yes
USE_LANGUAGES=		c c++
USE_TOOLS+=		gmake

.include "options.mk"

.include "../../security/openssl/buildlink3.mk"
# system.h declares struct utimbuf unless told it exists; IRIX's headers
# bring in <utime.h>, which has it.
CPPFLAGS.IRIX+=	-DHAVE_STRUCT_UTIMBUF

.include "../../mk/bsd.pkg.mk"
