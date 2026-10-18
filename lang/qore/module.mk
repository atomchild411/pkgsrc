# $NetBSD: module.mk,v 1.3 2022/10/20 10:14:01 nros Exp $
#
# This file should be included in the makefile of packages that install
# Qore modules.
#
# PLIST variables:
#
# QORE_VERSION 		 To be used by packages that install files in
# 			 ${QORE_MODULE_DIR}/${QORE_VERSION}/
#
# QORE_MODULE_API	 This should be used by packages that install
# 			 modules that uses the compatible module api
#			 version.
#
# QORE_MODULE_DIR	 The directory where binary modules are
#			 installed relative to ${PREFIX}.
#
#
# QORE_LATEST_MODULE_API This should be used by packages that install
#			 modules that uses the latest module api
#			 version.
#
# QORE_USER_MODULE_DIR	 The directory where users modules(qm files) are
#			 installed relative to ${PREFIX}.
#
#
#

qore-module: post-install .PHONY

.include "../../mk/bsd.fast.prefs.mk"

.if ${USE_CROSS_COMPILE:U:tl} != "yes"
qore-version=qore --short-version | ${SED} -e s/-.*//
qore-module-api=qore --module-api
qore-module-dir=qore --module-dir
qore-latest-module-api=qore --latest-module-api
qore-user-module-dir=qore --user-module-dir
.else
# The qore installed for the target does not run on the build host.  Read
# what it would say from its files, and build qpp, the preprocessor that
# makes C++ from a module's .qpp files, from qore's source for the build
# host.  Both go in the tools directory for modules' configure and make
# (a "qore" there answers the questions below); CMake modules take qpp as
# QPP_EXECUTABLE.
_QORE_DIR=		${CROSS_DESTDIR}${LOCALBASE}
_QORE_CMAKE=		${_QORE_DIR}/lib/cmake/Qore/QoreConfig.cmake
_QORE_API=		${AWK} '/define QORE_MODULE_API_MAJOR/ { M = $$3 } \
			    /define QORE_MODULE_API_MINOR/ { m = $$3 } \
			    END { print M "." m }' \
			    ${_QORE_DIR}/include/qore/ModuleManager.h
qore-version=${SED} -n -e 's/^Version: //p' ${_QORE_DIR}/lib/pkgconfig/qore.pc
qore-module-api=${_QORE_API}
qore-module-dir=${SED} -n -e 's,^ *set(QORE_MODULES_DIR \(/.*\))$$,\1,p' ${_QORE_CMAKE}
qore-latest-module-api=${_QORE_API}
qore-user-module-dir=${SED} -n -e 's,^ *set(QORE_USER_MODULES_DIR \(/.*\))$$,\1,p' ${_QORE_CMAKE}

# Keep in step with lang/qore.
_QORE_QPP_DIST=		qore-1.19.2
_QORE_QPP_DISTFILE=	${_QORE_QPP_DIST}.tar.bz2
DISTFILES?=		${DEFAULT_DISTFILES}
DISTFILES+=		${_QORE_QPP_DISTFILE}
EXTRACT_ONLY?=		${DISTFILES:N${_QORE_QPP_DISTFILE}}
SITES.${_QORE_QPP_DISTFILE}= \
	${MASTER_SITE_GITHUB:=qorelanguage/qore/releases/download/release-${_QORE_QPP_DIST:S/qore-//}/}
USE_TOOLS+=		bzip2
_QORE_QPP_NATIVE=	${TOOLS_DIR}/bin/qpp
CMAKE_CONFIGURE_ARGS+=	-DQPP_EXECUTABLE=${_QORE_QPP_NATIVE}

pre-configure: qore-cross-tools
.PHONY: qore-cross-tools
qore-cross-tools:
	${RUN} ${MKDIR} ${WRKDIR}/qpp/qore/intern ${TOOLS_DIR}/bin
	${RUN} cd ${WRKDIR}/qpp && ${EXTRACTOR} ${_DISTDIR}/${_QORE_QPP_DISTFILE} \
		${_QORE_QPP_DIST}/lib/qpp.cpp ${_QORE_QPP_DIST}/include
	${RUN} ${ECHO} '#define HAVE_GETOPT_H 1' > ${WRKDIR}/qpp/qore/intern/unix-config.h
	${RUN} ${NATIVE_CXX} -O2 -DHAVE_UNIX_CONFIG_H -I${WRKDIR}/qpp	\
		-I${WRKDIR}/qpp/${_QORE_QPP_DIST}/include			\
		-I${WRKDIR}/qpp/${_QORE_QPP_DIST}/lib -o ${_QORE_QPP_NATIVE}	\
		${WRKDIR}/qpp/${_QORE_QPP_DIST}/lib/qpp.cpp
	${RUN} { ${ECHO} '#!${SH}';					\
		${ECHO} 'case "$$1" in';					\
		${ECHO} '--short-version) echo ${qore-version:sh} ;;';		\
		${ECHO} '--module-api) echo ${qore-module-api:sh} ;;';		\
		${ECHO} '--latest-module-api) echo ${qore-latest-module-api:sh} ;;'; \
		${ECHO} '--module-dir) echo ${qore-module-dir:sh} ;;';		\
		${ECHO} '--user-module-dir) echo ${qore-user-module-dir:sh} ;;'; \
		${ECHO} '*) echo "qore: only for questions in cross builds" >&2; exit 1 ;;'; \
		${ECHO} 'esac'; } > ${TOOLS_DIR}/bin/qore
	${RUN} ${CHMOD} +x ${TOOLS_DIR}/bin/qore
.endif
PLIST_SUBST+=QORE_VERSION="${qore-version:sh}"
PLIST_SUBST+=QORE_MODULE_API="${qore-module-api:sh}"
PLIST_SUBST+=QORE_MODULE_DIR="${qore-module-dir:sh:C,^${PREFIX}/,,W}"
PLIST_SUBST+=QORE_LATEST_MODULE_API="${qore-latest-module-api:sh}"
PLIST_SUBST+=QORE_USER_MODULE_DIR="${qore-user-module-dir:sh:C,^${PREFIX}/,,W}"
PRINT_PLIST_AWK+= { gsub("^${qore-module-dir:sh:C,^${PREFIX}/,,W}", "$${QORE_MODULE_DIR}"); }
PRINT_PLIST_AWK+= { gsub("^${qore-user-module-dir:sh:C,^${PREFIX}/,,W}", "$${QORE_USER_MODULE_DIR}"); }
PRINT_PLIST_AWK+= /.*\.qmod$$/ { gsub("${qore-latest-module-api:sh}", "$${QORE_LATEST_MODULE_API}"); }
