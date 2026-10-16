# $NetBSD: buildlink3.mk,v 1.22 2026/02/17 12:06:50 wiz Exp $

BUILDLINK_TREE+=	py-numpy

.if !defined(PY_NUMPY_BUILDLINK3_MK)
PY_NUMPY_BUILDLINK3_MK:=

USE_CXX_FEATURES+=	c++17

.include "../../lang/python/pyversion.mk"

BUILDLINK_API_DEPENDS.py-numpy+=	${PYPKGPREFIX}-numpy>=1.0
BUILDLINK_ABI_DEPENDS.py-numpy+=	${PYPKGPREFIX}-numpy>=1.20.3nb1
BUILDLINK_PKGSRCDIR.py-numpy?=		../../math/py-numpy

BUILDLINK_TARGETS+=	buildlink-numpy-unversioned
.PHONY: buildlink-numpy-unversioned
buildlink-numpy-unversioned:
	${LN} -s ${PREFIX}/${PYSITELIB}/numpy/_core/lib/pkgconfig/numpy.pc \
		${BUILDLINK_DIR}/lib/pkgconfig/numpy.pc

.include "../../mk/bsd.fast.prefs.mk"

.include "../../math/py-numpy/make_env.mk"

# IRIX: numpy is built without BLAS or LAPACK (see Makefile).
.if ${OPSYS} != "IRIX"
BLAS_C_INTERFACE=	yes
.include "../../mk/blas.buildlink3.mk"
.endif

# Cross-compiling, the build host's python cannot import the target's numpy
# (its extensions are the target's): give it a stand-in with the target's
# version and include directory, which is what builds ask numpy for.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
pre-configure: ${WRKDIR}/.pysite/numpy/__init__.py
${WRKDIR}/.pysite/numpy/__init__.py:
	@${STEP_MSG} "Creating a numpy stand-in for cross-compiling"
	${RUN} ${MKDIR} ${.TARGET:H}
	${RUN} (							\
	  ${ECHO} "import os";						\
	  ${ECHO} "_d = '${_CROSS_DESTDIR}${PREFIX}/${PYSITELIB}/numpy'";	\
	  ${ECHO} "exec(open(os.path.join(_d, 'version.py')).read())";	\
	  ${ECHO} "def get_include():";					\
	  ${ECHO} "    return os.path.join(_d, '_core', 'include')";	\
	) > ${.TARGET}
# and its declarations for Cython (cimport numpy: pandas)
	${RUN} for f in ${_CROSS_DESTDIR}${PREFIX}/${PYSITELIB}/numpy/*.pxd; do	\
	  [ -f "$$f" ] && ${LN} -sf "$$f" ${.TARGET:H}/;		\
	done; ${TRUE}
.endif

.endif # PY_NUMPY_BUILDLINK3_MK

BUILDLINK_TREE+=	-py-numpy
