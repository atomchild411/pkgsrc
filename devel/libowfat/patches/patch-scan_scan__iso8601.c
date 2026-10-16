$NetBSD: patch-scan_scan__iso8601.c,v 1.2 2022/11/03 00:00:08 schmonz Exp $

Fix Illumos (and IRIX) build. Then fix macOS build with the 13.0 SDK, which has its
own definition of __deprecated__.

--- scan/scan_iso8601.c.orig
+++ scan/scan_iso8601.c
@@ -6,6 +6,9 @@
 #include "byte.h"
 #include "case.h"
 #include <time.h>
+#ifdef __APPLE__
+#undef __deprecated__
+#endif
 #include <stdlib.h>
 
 #ifdef sgi
@@ -46,7 +49,7 @@ size_t scan_iso8601(const char* in,struc
     }
   }
 
-#ifdef __MINGW32__
+#if defined(__MINGW32__) || (defined (__sun__) && defined(__svr4__)) || defined(sgi)
   x.tm_wday=x.tm_yday=x.tm_isdst=0;
 #else
   x.tm_wday=x.tm_yday=x.tm_isdst=x.tm_gmtoff=0;
