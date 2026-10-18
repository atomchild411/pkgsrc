$NetBSD$

IRIX: a static named time clashes with ::time from <time.h>.

--- snowball.cc.orig
+++ snowball.cc
@@ -24,6 +24,8 @@
 static int an;
 static long subKind;
 static long ve;
+/* IRIX: <time.h> declares ::time here. */
+#define time toppler_snowball_time
 static long time;
 
 void snb_init(void) {
