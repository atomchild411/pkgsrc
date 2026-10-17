$NetBSD$

stub: the GLIBTOP_SUID_PROC_AFFINITY, _OPEN_FILES and _WD flags.

--- sysdeps/stub/glibtop_server.h.orig
+++ sysdeps/stub/glibtop_server.h
@@ -45,6 +45,9 @@
 #define GLIBTOP_SUID_NETLOAD		0
 #define GLIBTOP_SUID_NETLIST		0
 #define GLIBTOP_SUID_PPP		0
+#define GLIBTOP_SUID_PROC_AFFINITY	0
+#define GLIBTOP_SUID_PROC_OPEN_FILES	0
+#define GLIBTOP_SUID_PROC_WD		0
 
 G_END_DECLS
 
