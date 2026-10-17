$NetBSD$

IRIX's <sys/types.h> has a global addr_t: give the alias another name there.

--- kernel/mem.cc.orig
+++ kernel/mem.cc
@@ -1680,7 +1680,13 @@
 	return res;
 }
 
+#ifdef __sgi
+// IRIX's <sys/types.h> has a global addr_t (a char *) of its own.
+using yosys_mem_addr_t = MemContents::addr_t;
+#define addr_t yosys_mem_addr_t
+#else
 using addr_t = MemContents::addr_t;
+#endif
 
 MemContents::MemContents(Mem *mem) :
 	MemContents(ceil_log2(mem->size), mem->width)
