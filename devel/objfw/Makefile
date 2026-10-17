# $NetBSD: Makefile,v 1.71 2026/07/03 22:07:19 js Exp $

DISTNAME=	objfw-1.5.7
PKGREVISION=	1
CATEGORIES=	devel
MASTER_SITES=	https://objfw.nil.im/downloads/

MAINTAINER=	js@NetBSD.org
HOMEPAGE=	https://objfw.nil.im/
COMMENT=	Portable, lightweight framework for the Objective-C language
LICENSE=	gnu-lgpl-v3

GNU_CONFIGURE=		yes
USE_LANGUAGES=		objc
CONFIGURE_ARGS+=	OBJCFLAGS=${CFLAGS:M*:Q}
CONFIGURE_ARGS+=	LDFLAGS=${LDFLAGS:M*:Q}

# Breaks exceptions in some rare cases with GCC on NetBSD 10 on AMD64 (e.g. on
# my system ofhttp would fail because an exception could not be caught, but the
# entire test suite would pass).
# Unfortunately, we cannot check if we are using Clang or GCC here, as this
# needs to be set before including bsd.prefs.mk, and hence also before
# options.mk.
STACK_CHECK_SUPPORTED=	no

.include "../../mk/bsd.prefs.mk"

# A cross configure names the tools for the host (mipseb-sgi-irix6.5-objfw-
# config and so on), for use beside a native ObjFW; the package is for the
# host itself.
.if ${USE_CROSS_COMPILE:tl} == "yes"
MAKE_FLAGS+=	BIN_PREFIX=
.endif

# IRIX's clang gives a C or Objective-C link no unwinder (elsewhere the
# compiler adds libgcc_s as needed), and lld does not look through
# libobjfw's own DT_NEEDED for _Unwind_Resume: objfw-config names the one
# configure found, libc++abi.
.if ${OPSYS} == "IRIX"
SUBST_CLASSES+=		unwind
SUBST_STAGE.unwind=	pre-configure
SUBST_MESSAGE.unwind=	Naming the unwinder in objfw-config.
SUBST_FILES.unwind=	utils/objfw-config.in
SUBST_SED.unwind=	-e '/^LIBS=/s|@OBJFW_LIBS@"|@OBJFW_LIBS@ -lc++abi"|'
SUBST_SED.unwind+=	-e '/^STATIC_LIBS=/s|@OBJFW_LIBS@"|@OBJFW_LIBS@ -lc++abi"|'
.endif

PLIST_SRC=	PLIST
PLIST_VARS+=	ddp ipx ofgctester sctp

.if ${OPSYS} == "Darwin"
PLIST_SRC+=		PLIST.bridge
PLIST_SRC+=		PLIST.framework
PLIST.ofgctester=	yes
.else
PLIST_SRC+=		PLIST.runtime
.endif

.if ${OPSYS} == "NetBSD"
PLIST.ddp=		yes
PLIST.sctp=		yes
.endif

.if ${OPSYS} == "FreeBSD"
PLIST.sctp=		yes
.endif

.if ${OPSYS} == "Linux"
PLIST.ddp=		yes
PLIST.ipx=		yes
PLIST.ofgctester=	yes
PLIST.sctp=		yes
.endif

do-test:
	${RUN} cd ${WRKSRC} && ${MAKE} check

.include "options.mk"

.include "../../mk/bsd.pkg.mk"
