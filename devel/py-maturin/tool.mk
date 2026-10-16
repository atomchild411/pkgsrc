# $NetBSD: tool.mk,v 1.2 2025/03/21 16:16:19 gdt Exp $
#
# Maturin will by default spawn as many build threads as it finds online
# CPUs, which is completely unsuitable for bulk builds.  This file should
# be used instead of a plain TOOL_DEPENDS so that MAKE_JOBS is correctly
# handled.

.if !defined(MATURIN_TOOL_MK)
MATURIN_TOOL_MK:=

# At least 1.7.8 fails to parse some now-considered-ok pyproject.toml
# content.
TOOL_DEPENDS+=	${PYPKGPREFIX}-maturin>=1.8.3:../../devel/py-maturin

WHEEL_ARGS+=	-Cbuild-args=${_MAKE_JOBS}

# Cross-compiling, maturin (and pyo3's build scripts) take the target
# Python's configuration from its _sysconfigdata in PYO3_CROSS_LIB_DIR;
# without it maturin looks in its own table of known targets ("Failed to
# find a CPython 3.13 interpreter in known sysconfig").
.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:tl} == "yes"
MAKE_ENV+=	PYO3_CROSS_LIB_DIR=${_CROSS_DESTDIR:Q}${LOCALBASE}/${PYLIB:Q}
.endif
.endif
