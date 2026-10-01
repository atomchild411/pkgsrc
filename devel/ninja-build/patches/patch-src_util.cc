$NetBSD$

IRIX has no getloadavg(); its load average is readable only through
/dev/kmem.  Report it unknown, as on Haiku.

--- src/util.cc.orig
+++ src/util.cc
@@ -973,7 +973,7 @@
     return -0.0f;
   return 1.0 / (1 << SI_LOAD_SHIFT) * si.loads[0];
 }
-#elif defined(__HAIKU__)
+#elif defined(__HAIKU__) || defined(__sgi)
 double GetLoadAverage() {
     return -0.0f;
 }
