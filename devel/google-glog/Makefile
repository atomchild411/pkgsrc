# $NetBSD: Makefile,v 1.16 2025/07/02 02:31:40 markd Exp $

DISTNAME=	glog-0.7.1
PKGNAME=	google-${DISTNAME}
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GITHUB:=google/}
GITHUB_PROJECT=	glog
GITHUB_TAG=	v${PKGVERSION_NOREV}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://github.com/google/glog
COMMENT=	Application Level Logging library for C++
LICENSE=	modified-bsd

USE_CXX_FEATURES=	c++14
USE_LANGUAGES=		c c++
USE_TOOLS+=		pkg-config

CMAKE_CONFIGURE_ARGS+=	-DWITH_UNWIND=none

BUILDLINK_TRANSFORM.SunOS+=	rm:-pie

.include "../../mk/bsd.prefs.mk"
.if (${OPSYS} == "NetBSD" || ${OPSYS} == "FreeBSD") && exists(/usr/include/execinfo.h)
LDFLAGS+=	-lexecinfo
.endif

# IRIX has <sys/syscall.h> but no syscall(): raw logging write()s instead.
# It has <elf.h> but not the <link.h> glog's ELF symbolizer needs: no
# symbol names in stack traces there.
.if ${OPSYS} == "IRIX"
CMAKE_CONFIGURE_ARGS+=	-DHAVE_SYS_SYSCALL_H:INTERNAL=
CMAKE_CONFIGURE_ARGS+=	-DHAVE_ELF_H:INTERNAL=
.endif

.include "options.mk"
.include "../../devel/cmake/build.mk"
.include "../../devel/gflags/buildlink3.mk"
.include "../../mk/atomic64.mk"
.include "../../mk/bsd.pkg.mk"
