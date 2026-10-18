$NetBSD$

IRIX: <math.h> defines qlog (as logl).

--- main/logger.c.orig
+++ main/logger.c
@@ -71,6 +71,10 @@
 #include "asterisk/backtrace.h"
 #include "asterisk/json.h"
 
+#ifdef qlog	/* IRIX <math.h>: qlog is logl */
+#undef qlog
+#endif
+
 /*** DOCUMENTATION
  ***/
 
