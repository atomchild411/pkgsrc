$NetBSD: patch-include_konoha1_konoha__config.h,v 1.2 2012/08/12 11:24:00 marino Exp $

* Add NetBSD support
* Add DragonFly support
* Add IRIX support

--- include/konoha1/konoha_config.h.orig
+++ include/konoha1/konoha_config.h
@@ -288,6 +288,17 @@
 #define     K_USING_SQLITE3     1
 #endif
 
+#if defined(__NetBSD__) /* NetBSD */
+#define		K_USING_PTHREAD
+#define		K_USING_STDC_    1
+#define 	K_USING_POSIX_      1
+#define 	K_USING_BSD_        1
+#define     K_USING_BSDSYSCTL_  1
+#define     K_USING_SYSLOG      1
+#define     K_USING_ICONV       1
+#define     K_USING_SQLITE3     1
+#endif
+
 #if defined(__MINGW32__)  /* mingw */
 #define		K_USING_STDC_       1
 #define		K_USING_SETJMP_     1
@@ -328,6 +339,17 @@
 
 /* experimetally supported */
 
+#if defined(__DragonFly__)
+#define K_USING_PTHREAD
+#define K_USING_STDC_       1
+#define K_USING_POSIX_      1
+#define K_USING_BSD_        1
+#define K_USING_BSDSYSCTL_  1
+#define K_USING_ICONV       1
+#define K_USING_SYSLOG      1
+#define K_USING_SQLITE3     1
+#endif
+
 #if defined(__FreeBSD__) /* FreeBSD */
 #define		K_USING_STDC_       1
 #define 	K_USING_POSIX_      1
@@ -360,6 +382,15 @@
 #endif
 
 
+#if defined(__sgi) /* IRIX */
+#define		K_USING_PTHREAD
+#define		K_USING_STDC_       1
+#define 	K_USING_POSIX_      1
+#define     K_USING_ICONV       1
+#define     K_USING_SYSLOG      1
+#define     K_USING_SQLITE3     1
+#endif
+
 /* THIS_MUST_BE_LAST_ONE */
 
 #if !defined(K_USING_STDC_) && (defined(__unix__) || defined(__unix) || defined(unix))
