# $NetBSD: Makefile,v 1.7 2026/02/15 18:21:05 gdt Exp $

DISTNAME=	jose-1.11.12
PKGREVISION=	1
CATEGORIES=	security
MASTER_SITES=	${MASTER_SITE_GITHUB:=potatosalad/}
GITHUB_PROJECT=	erlang-jose

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://hexdocs.pm/jose/JOSE.html
COMMENT=	JSON Object Signing and Encryption
LICENSE=	mpl-2.0

WRKSRC=		${WRKDIR}/${PKGNAME_NOREV}
USE_LANGUAGES=	# none
USE_TOOLS+=	gmake

TOOL_DEPENDS+=	elixir>=1.17.0:../../lang/elixir

MAKE_FLAGS+=	SKIP_DEPS=true
# The Makefile knows only amd64 and arm64 (ARCH just names an ELP
# download), erlang.mk not IRIX.
MAKE_FLAGS+=	ARCH=${MACHINE_ARCH}
MAKE_ENV.IRIX+=	PLATFORM=linux

# Fails to build if a previous erlang-jose is not installed.
# https://github.com/potatosalad/erlang-jose/issues/189

.include "../../lang/erlang/module.mk"

# The Elixir part reads jose's own .hrl files through the code path, so
# that a previous jose had to be installed (upstream issue 189): put the
# source tree there (cross.mk sets ERL_LIBS to this when cross-compiling).
.if ${USE_CROSS_COMPILE:U:tl} != "yes"
MAKE_ENV+=	ERL_LIBS=${WRKDIR}/.erl_libs
.endif
pre-build:
	${MKDIR} ${WRKDIR}/.erl_libs
	${LN} -sf ${WRKSRC} ${WRKDIR}/.erl_libs/jose
.include "../../mk/bsd.pkg.mk"
