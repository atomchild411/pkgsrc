# $NetBSD: buildlink3.mk,v 1.29 2026/08/26 10:19:05 adam Exp $

BUILDLINK_TREE+=	protobuf

.if !defined(PROTOBUF_BUILDLINK3_MK)
PROTOBUF_BUILDLINK3_MK:=

USE_CXX_FEATURES+=	c++14

BUILDLINK_API_DEPENDS.protobuf+=	protobuf>=24.4
BUILDLINK_ABI_DEPENDS.protobuf+=	protobuf>=36.0
BUILDLINK_PKGSRCDIR.protobuf?=		../../devel/protobuf

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == yes
# protoc runs at build time: use the build machine's, of this version.
TOOL_DEPENDS+=		protobuf>=36.0:../../devel/protobuf
PROTOC=			${TOOLBASE}/bin/protoc
CONFIGURE_ENV+=		PROTOC=${PROTOC:Q}
MAKE_ENV+=		PROTOC=${PROTOC:Q}
CMAKE_CONFIGURE_ARGS+=	-DProtobuf_PROTOC_EXECUTABLE=${PROTOC:Q}
# protobuf's CMake package imports protobuf::protoc (and the upb plugins)
# from bin/protoc-<version> and refuses to load when a file is missing: the
# build machine's go there, which are also the ones a project that runs
# them needs.
BUILDLINK_TARGETS+=	protobuf-buildlink-host-protoc
.PHONY: protobuf-buildlink-host-protoc
protobuf-buildlink-host-protoc:
	${RUN} ${MKDIR} ${BUILDLINK_DIR}/bin;				\
	for f in ${TOOLBASE}/bin/protoc-[0-9]* ${TOOLBASE}/bin/protoc-gen-upb*-[0-9]*; do \
		if [ -f "$$f" ]; then ${LN} -sf "$$f" ${BUILDLINK_DIR}/bin/; fi; \
	done
.else
BUILDLINK_FILES.protobuf+=	bin/protoc
BUILDLINK_FILES.protobuf+=	bin/protoc-*
.endif
.include "../../devel/abseil/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.endif	# PROTOBUF_BUILDLINK3_MK

BUILDLINK_TREE+=	-protobuf
