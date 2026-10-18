$NetBSD$

sig_atomic_t needs <signal.h>.

--- src/ircd_signal.h.orig
+++ src/ircd_signal.h
@@ -27,6 +27,8 @@
 #ifndef INCLUDED_ircd_signal_h
 #define INCLUDED_ircd_signal_h
 
+#include <signal.h>  /* sig_atomic_t */
+
 /**
  * @var dorehash
  * @brief Flag indicating if the server configuration should be re-read.
