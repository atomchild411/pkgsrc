$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libc++: support IRIX 6.5

--- src/memory_resource.cpp.orig
+++ src/memory_resource.cpp
@@ -137,6 +137,11 @@ memory_resource* set_default_resource(memory_resource* __new_res) noexcept {
 
 // 23.12.5, mem.res.pool
 
+// IRIX's <sys/param.h> has a roundup macro.
+#ifdef roundup
+#  undef roundup
+#endif
+
 static size_t roundup(size_t count, size_t alignment) {
   size_t mask = alignment - 1;
   return (count + mask) & ~mask;
