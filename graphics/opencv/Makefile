# $NetBSD: Makefile,v 1.167 2026/09/02 19:02:49 wiz Exp $

PKGREVISION= 3
.include "Makefile.common"

DISTNAME=	opencv-${OPENCV_VERSION}

MAINTAINER=	anthony.mallet@laas.fr
COMMENT=	Library for computer vision problems

PY_PATCHPLIST=		yes
REPLACE_PYTHON+=	samples/python/*.py

PYTHON_VERSIONS_INCOMPATIBLE=	310 311

CMAKE_CONFIGURE_ARGS+=	-DPYTHON_EXECUTABLE=${PYTHONBIN}

PLIST_VARS+=	itt opencl

.include "../../mk/bsd.prefs.mk"
.if ${OPSYS} != "Darwin"
PLIST.opencl=	yes
.endif
# Intel's ITT (ittnotify) is built only for these processors.
.if ${MACHINE_ARCH} == "i386" || ${MACHINE_ARCH} == "x86_64" || \
    !empty(MACHINE_ARCH:M*arm*) || !empty(MACHINE_ARCH:Maarch64*) || \
    ${MACHINE_ARCH} == "powerpc64le"
PLIST.itt=	yes
.endif

# Cross compiling, OpenCV cannot probe the target's Python and NumPy, and
# leaves the bindings out unless told where they are (the target's, from
# the cross destdir; numpy's buildlink3.mk has the same directory) and
# where they go. Its generators run the build machine's python.
.if ${USE_CROSS_COMPILE:tl} == "yes"
CMAKE_CONFIGURE_ARGS+=	-DPYTHON3_EXECUTABLE=${TOOL_PYTHONBIN}
CMAKE_CONFIGURE_ARGS+=	-DPYTHON3_INCLUDE_PATH=${BUILDLINK_DIR}/${PYINC}
CMAKE_CONFIGURE_ARGS+=	-DPYTHON3_LIBRARIES=${BUILDLINK_DIR}/lib/libpython${PYVERSSUFFIX}.so
CMAKE_CONFIGURE_ARGS+=	-DPYTHON3_NUMPY_INCLUDE_DIRS=${_CROSS_DESTDIR}${PREFIX}/${PYSITELIB}/numpy/_core/include
CMAKE_CONFIGURE_ARGS+=	-DPYTHON3_PACKAGES_PATH=${PREFIX}/${PYSITELIB}
.endif

.include "options.mk"

TEST_ENV+=	LD_LIBRARY_PATH=${WRKSRC}/${CMAKE_BUILD_DIR}/lib
# For Darwin
TEST_ENV+=	DYLD_LIBRARY_PATH=${WRKSRC}/${CMAKE_BUILD_DIR}/lib
TEST_TARGET=	test

post-install:
	${MV} ${DESTDIR}${PREFIX}/share/licenses/opencv4 ${DESTDIR}${PREFIX}/share/opencv4/licenses

.include "../../devel/protobuf/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../graphics/libavif/buildlink3.mk"
.include "../../graphics/libwebp/buildlink3.mk"
.include "../../graphics/openexr/buildlink3.mk"
BUILDLINK_API_DEPENDS.openjpeg+=	openjpeg>=2.3.1
.include "../../graphics/openjpeg/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../graphics/tiff/buildlink3.mk"
.include "../../lang/python/extension.mk"
.include "../../math/py-numpy/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
