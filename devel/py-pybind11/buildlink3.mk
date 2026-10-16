# $NetBSD: buildlink3.mk,v 1.5 2023/12/29 20:27:03 tnn Exp $

BUILDLINK_TREE+=	py-pybind11

.if !defined(PY_PYBIND11_BUILDLINK3_MK)
PY_PYBIND11_BUILDLINK3_MK:=

# As this package defaults to DEPMETHOD=build we also set python to default
# to build, and avoid pulling in unwanted indirect buildlink3 dependencies.
PYTHON_FOR_BUILD_ONLY?=		yes
.include "../../lang/python/pyversion.mk"

pre-configure: py-pybind11-preconfigure

.PHONY: py-pybind11-preconfigure
py-pybind11-preconfigure:
	${LN} -sf ${PREFIX}/bin/pybind11-config-${PYVERSSUFFIX} ${BUILDLINK_DIR}/bin/pybind11-config

BUILDLINK_API_DEPENDS.py-pybind11+=	${PYPKGPREFIX}-pybind11>=2.5.0
BUILDLINK_PKGSRCDIR.py-pybind11?=	../../devel/py-pybind11
BUILDLINK_DEPMETHOD.py-pybind11?=	build

.include "../../mk/bsd.fast.prefs.mk"
# Cross-compiling, pybind11-config is the build host's, and names its
# headers there: the same headers, the target package's, are buildlinked.
.if ${USE_CROSS_COMPILE:U:tl} == "yes"
BUILDLINK_TRANSFORM+=	I:${TOOLBASE}/${PYSITELIB}/pybind11/include:${BUILDLINK_DIR}/${PYSITELIB}/pybind11/include
.endif

.endif	# PY_PYBIND11_BUILDLINK3_MK

BUILDLINK_TREE+=	-py-pybind11
