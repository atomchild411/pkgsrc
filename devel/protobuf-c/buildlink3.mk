# $NetBSD: buildlink3.mk,v 1.19 2026/08/26 10:19:05 adam Exp $

BUILDLINK_TREE+=	protobuf-c

.if !defined(PROTOBUF_C_BUILDLINK3_MK)
PROTOBUF_C_BUILDLINK3_MK:=

BUILDLINK_API_DEPENDS.protobuf-c+=	protobuf-c>=1.1.1
BUILDLINK_ABI_DEPENDS.protobuf-c+=	protobuf-c>=1.5.2nb5
BUILDLINK_PKGSRCDIR.protobuf-c?=	../../devel/protobuf-c

.include "../../mk/bsd.fast.prefs.mk"
.if ${USE_CROSS_COMPILE:U:tl} == yes
# protoc-c runs at build time: the build machine's, first in PATH
# (configure scripts and makefiles run plain protoc-c).
TOOL_DEPENDS+=		protobuf-c>=1.1.1:../../devel/protobuf-c
buildlink-protobuf-c-cookie: buildlink-protobuf-c-protoc-c
.PHONY: buildlink-protobuf-c-protoc-c
buildlink-protobuf-c-protoc-c: buildlink-directories
	${MKDIR} ${BUILDLINK_DIR}/bin
	${LN} -fs ${TOOLBASE}/bin/protoc-c ${BUILDLINK_DIR}/bin/protoc-c
.endif

.include "../../devel/protobuf/buildlink3.mk"
.endif	# PROTOBUF_C_BUILDLINK3_MK

BUILDLINK_TREE+=	-protobuf-c
