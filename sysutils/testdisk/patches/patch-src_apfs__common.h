$NetBSD$

IRIX: <sys/types.h> defines paddr_t; its uuid_create is DCE's.

--- src/apfs_common.h.orig
+++ src/apfs_common.h
@@ -34,6 +34,9 @@
   } __attribute__((gcc_struct, __packed__));
 
   typedef struct obj_phys obj_phys_t;
+  /* IRIX's <sys/types.h> has a paddr_t (unsigned long): rename APFS's. */
+#include <sys/types.h>
+#define paddr_t apfs_paddr_t
   typedef int64_t paddr_t;
 
   struct prange {
