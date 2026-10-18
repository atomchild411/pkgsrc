$NetBSD$

IRIX: no musttail (LLVM cannot lower it on MIPS), and no reentrant resolver for SRV lookups.

--- cdk/extra/protobuf/protobuf-3.19.6/src/google/protobuf/port_def.inc.orig
+++ cdk/extra/protobuf/protobuf-3.19.6/src/google/protobuf/port_def.inc
@@ -230,7 +230,8 @@
 #error PROTOBUF_TAILCALL was previously defined
 #endif
 #if __has_cpp_attribute(clang::musttail) && \
-  !defined(__arm__) && !defined(_ARCH_PPC) && !defined(__wasm__)
+  !defined(__arm__) && !defined(_ARCH_PPC) && !defined(__wasm__) && \
+  !defined(__mips__)
 #  ifndef PROTO2_OPENSOURCE
 // Compilation fails on ARM32: b/195943306
 // Compilation fails on powerpc64le: b/187985113
