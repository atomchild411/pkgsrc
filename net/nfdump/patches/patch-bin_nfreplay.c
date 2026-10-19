$NetBSD$

Neither fpurge nor __fpurge (IRIX): fall back to fflush.

--- bin/nfreplay.c.orig
+++ bin/nfreplay.c
@@ -87,6 +87,9 @@
 #ifdef	HAVE_FPURGE
 #define	FPURGE	fpurge
 #endif
+#ifndef	FPURGE
+#define	FPURGE	fflush	/* SysV (IRIX): discards buffered input */
+#endif
 
 /* Externals */
 extern int yydebug;
