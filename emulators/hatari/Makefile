# $NetBSD: Makefile,v 1.79 2026/09/02 19:01:56 wiz Exp $

DISTNAME=	hatari-v2.6.1
PKGNAME=	${DISTNAME:S/-v/-/}
PKGREVISION=	2
CATEGORIES=	emulators
MASTER_SITES=	https://framagit.org/hatari/hatari/-/archive/v${PKGVERSION_NOREV}/
EXTRACT_SUFX=	.tar.bz2

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://hatari.tuxfamily.org/
COMMENT=	Atari ST emulator
LICENSE=	gnu-gpl-v2

USE_CC_FEATURES=	c99
USE_LANGUAGES=		c
CMAKE_CONFIGURE_ARGS+=	-DENABLE_OSX_BUNDLE=OFF
CMAKE_CONFIGURE_ARGS+=	-DMANDIR=${PKGMANDIR}/man1

REPLACE_PYTHON+=	python-ui/config.py
REPLACE_PYTHON+=	python-ui/debugui.py
REPLACE_PYTHON+=	python-ui/dialogs.py
REPLACE_PYTHON+=	python-ui/gentypes.py
REPLACE_PYTHON+=	python-ui/hatari.py
REPLACE_PYTHON+=	python-ui/hatariui.py
REPLACE_PYTHON+=	python-ui/uihelpers.py
REPLACE_PYTHON+=	tests/tosboot/tos_tester.py
REPLACE_PYTHON+=	tools/atari-convert-dir.py
REPLACE_PYTHON+=	tools/debugger/hatari_profile.py
REPLACE_PYTHON+=	tools/debugger/hatari_spinloop.py
REPLACE_PYTHON+=	tools/hconsole/example.py
REPLACE_PYTHON+=	tools/hconsole/hconsole.py

INSTALLATION_DIRS+=	share/doc/hatari

.include "../../mk/bsd.prefs.mk"

.if ${USE_CROSS_COMPILE:U:tl} == "yes"
# build68k and gencpu generate the CPU core during the build; the cross
# branch compiles them with "cc", which is the target's here.
SUBST_CLASSES+=		hostcc
SUBST_STAGE.hostcc=	pre-configure
SUBST_FILES.hostcc=	src/cpu/CMakeLists.txt
SUBST_SED.hostcc=	-e 's,COMMAND cc -I,COMMAND ${NATIVE_CC} -I,'
SUBST_MESSAGE.hostcc=	Building the CPU generators for the build host.
# The Python GTK probe would find the build machine's PyGObject and add
# hatariui, which the PLIST leaves out (no py-gobject dependency).
SUBST_CLASSES+=		nopyui
SUBST_STAGE.nopyui=	pre-configure
SUBST_FILES.nopyui=	CMakeLists.txt
SUBST_SED.nopyui=	-e 's,^if(Python_Interpreter_FOUND)$$,if(FALSE),'
SUBST_MESSAGE.nopyui=	Not installing the Python UI.
.endif

.include "../../audio/portaudio/buildlink3.mk"
.include "../../devel/SDL2/buildlink3.mk"
.include "../../devel/cmake/build.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/hicolor-icon-theme/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../lang/python/application.mk"
.include "../../sysutils/desktop-file-utils/desktopdb.mk"
.if ${OPSYS} != "Darwin"
.include "../../x11/libXext/buildlink3.mk"
.include "../../x11/libX11/buildlink3.mk"
.endif
.include "../../mk/readline.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
