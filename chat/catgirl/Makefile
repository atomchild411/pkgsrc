# $NetBSD: Makefile,v 1.8 2025/07/25 19:30:09 vins Exp $

DISTNAME=	catgirl-2.2a
PKGREVISION=	1
CATEGORIES=	chat
MASTER_SITES=	https://git.causal.agency/catgirl/snapshot/

MAINTAINER=	vins@NetBSD.org
HOMEPAGE=	https://git.causal.agency/catgirl/about/
COMMENT=	TLS-only terminal IRC client
LICENSE=	gnu-gpl-v3

USE_TOOLS+=	pkg-config

HAS_CONFIGURE=	yes

MAKE_FLAGS=	MANDIR=${PREFIX}/${PKGMANDIR}

USE_CC_FEATURES+=	c11

.include "../../mk/bsd.prefs.mk"

# On IRIX catgirl takes configure's generic branch, as the BSDs do, whose
# headers give sig_t even under -std=c11; IRIX's (clang's wrappers) give it
# only outside strict C: GNU C11.
.if ${OPSYS} == "IRIX"
BUILDLINK_TRANSFORM+=	opt:-std=c11:-std=gnu11
.endif

# IRIX has no readpassphrase either: catgirl's own, as on Linux.
.if ${OPSYS} == "IRIX"
post-configure:
	${ECHO} 'OBJS += compat_readpassphrase.o' >> ${WRKSRC}/config.mk
.endif

SUBST_CLASSES+=		ssl
SUBST_STAGE.ssl=	pre-configure
SUBST_MESSAGE.ssl=	Correcting the hardcoded path to OpenSSL.
SUBST_FILES.ssl+=	configure
SUBST_SED.ssl+=		-e "s,OPENSSL_BIN /usr/bin/openssl,OPENSSL_BIN ${SSLBASE}/bin/openssl,g"
SUBST_SED.ssl+=		-e "s,OPENSSL_BIN /bin/openssl,OPENSSL_BIN ${SSLBASE}/bin/openssl,g"

.include "../../devel/ncurses/buildlink3.mk"
.include "../../security/libretls/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
