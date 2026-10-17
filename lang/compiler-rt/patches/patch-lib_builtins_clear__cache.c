$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- __clear_cache through _flush_cache, without rdhwr

--- lib/builtins/clear_cache.c.orig
+++ lib/builtins/clear_cache.c
@@ -42,6 +42,10 @@ uintptr_t GetCurrentProcess(void);
 // clang-format on
 #endif
 
+#if defined(__sgi) && defined(__mips__)
+#include <sys/cachectl.h>
+#endif
+
 #if defined(__linux__) && defined(__mips__)
 #include <sys/cachectl.h>
 #include <sys/syscall.h>
@@ -96,6 +100,12 @@ void __clear_cache(void *start, void *end) {
 #endif
 #elif defined(__linux__) && defined(__loongarch__)
   __asm__ volatile("ibar 0");
+#elif defined(__mips__) && defined(__sgi)
+  // IRIX runs on CPUs from before MIPS32r2 (R4000 to R16000), which have no
+  // rdhwr: reading SYNCI_Step below is an illegal instruction there. Its
+  // cache flush call writes back the data cache and invalidates the
+  // instruction cache.
+  _flush_cache((char *)start, (char *)end - (char *)start, BCACHE);
 #elif defined(__mips__)
   const uintptr_t start_int = (uintptr_t)start;
   const uintptr_t end_int = (uintptr_t)end;
