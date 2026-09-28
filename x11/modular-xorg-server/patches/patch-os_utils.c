$NetBSD$

Systems without O_NOFOLLOW (IRIX): define it as 0.

--- os/utils.c.orig
+++ os/utils.c
@@ -184,6 +184,10 @@
 #include <X11/Xos_r.h>
 
 #include <errno.h>
+
+#ifndef O_NOFOLLOW
+#define O_NOFOLLOW 0
+#endif
 
 Bool CoreDump;
 
