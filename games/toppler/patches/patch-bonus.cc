$NetBSD$

IRIX: a static named time clashes with ::time from <time.h>.

--- bonus.cc.orig
+++ bonus.cc
@@ -46,6 +46,9 @@
  */
 static Sint32 torpedox, torpedoy, subposx, subposy;
 
+/* IRIX: <time.h> declares ::time here. */
+#define time toppler_bonus_time
+
 /* current game time
  */
 static Sint32 time;
