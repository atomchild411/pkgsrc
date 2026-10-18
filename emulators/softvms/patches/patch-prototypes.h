$NetBSD$

IRIX declares gettimeofday(struct timeval *, ...).

--- prototypes.h.orig
+++ prototypes.h
@@ -8,7 +8,9 @@
 extern int do_lcdimg(char *filename);
 extern void sound(int freq);
 #ifdef BSD_STYLE_GETTIMEOFDAY
-#ifdef TIMEZONE_IS_VOID
+#if defined(__sgi)
+/* IRIX's <sys/time.h> declares gettimeofday(struct timeval *, ...) */
+#elif defined(TIMEZONE_IS_VOID)
 extern int gettimeofday(struct timeval *, void *);
 #else
 extern int gettimeofday(struct timeval *, struct timezone *);
