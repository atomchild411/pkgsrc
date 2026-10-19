$NetBSD$

IRIX declares usleep (returning int) in <unistd.h>.

--- graphics.h.orig
+++ graphics.h
@@ -72,6 +72,6 @@
 #define HIGH_SCORE_TABLE ".xemeraldia.scores"
 #endif
 
-#if defined(sgi) || defined(SYSV) || defined(SVR4)
+#if (defined(sgi) || defined(SYSV) || defined(SVR4)) && !defined(__sgi)
 void  usleep ();
 #endif
