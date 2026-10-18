$NetBSD$

IRIX <unistd.h> defines EX_OK.

--- main.h.orig
+++ main.h
@@ -10,6 +10,9 @@
 #include <stdio.h>
 
 
+/* IRIX's <unistd.h> defines EX_OK (an access() mode). */
+#undef EX_OK
+
 /**
  * Error codes as specified in sendmail's sysexits.h
  */
