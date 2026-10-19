# $NetBSD: Makefile,v 1.36 2026/05/14 16:40:25 ryoon Exp $

DISTNAME=	libmusicbrainz-5.1.0
PKGNAME=	${DISTNAME:S/brainz/brainz5/}
PKGREVISION=	23
CATEGORIES=	audio
MASTER_SITES=	${MASTER_SITE_GITHUB:=metabrainz/}
GITHUB_PROJECT=	libmusicbrainz
GITHUB_RELEASE=	release-${PKGVERSION_NOREV}
EXTRACT_USING=	bsdtar

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://musicbrainz.org/doc/libmusicbrainz
COMMENT=	MusicBrainz (user-maintained community music metadatabase) library v5
LICENSE=	gnu-lgpl-v2.1

USE_CMAKE=		yes
USE_LANGUAGES=		c c++
USE_TOOLS+=		pkg-config
PKGCONFIG_OVERRIDE=	libmusicbrainz5.pc.cmake

CMAKE_CONFIGURE_ARGS+=	-DCMAKE_POLICY_VERSION_MINIMUM=3.5

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# A cross build imports make-c-interface (it writes the C interface during
# the build) from a native build: build it for the build host after
# configure (it needs config.h; the build machine's libxml2) and hand
# cmake an import file for it.
CMAKE_CONFIGURE_ARGS+=	-DIMPORT_EXECUTABLES=${WRKDIR}/ImportExecutables.cmake

pre-configure:
	${PRINTF} 'add_executable(make-c-interface IMPORTED)\nset_property(TARGET make-c-interface PROPERTY IMPORTED_LOCATION %s)\n' \
		${WRKDIR}/make-c-interface > ${WRKDIR}/ImportExecutables.cmake

post-configure:
	cd ${WRKSRC}/src && ${NATIVE_CXX} -I${WRKSRC} -I${WRKSRC}/include \
		-I${TOOLBASE}/include/libxml2 \
		-o ${WRKDIR}/make-c-interface make-c-interface.cc xmlParser.cc \
		-L${TOOLBASE}/lib -Wl,-rpath,${TOOLBASE}/lib -lxml2
.endif

.include "../../devel/gettext-lib/buildlink3.mk"
BUILDLINK_API_DEPENDS.neon+=	neon>=0.25.0
.include "../../www/neon/buildlink3.mk"
.include "../../textproc/libxml2/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
