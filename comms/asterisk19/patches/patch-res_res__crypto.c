$NetBSD$

IRIX: no d_type, ALLPERMS or TCP keepalive names.

--- res/res_crypto.c.orig
+++ res/res_crypto.c
@@ -57,6 +57,10 @@
 #define AST_API_MODULE
 #include "asterisk/crypto.h"        /* for AST_KEY_PUBLIC, AST_KEY_PRIVATE */
 
+#ifndef ALLPERMS	/* not on IRIX */
+#define ALLPERMS	(S_ISUID|S_ISGID|S_ISVTX|S_IRWXU|S_IRWXG|S_IRWXO)
+#endif
+
 /*
  * Asterisk uses RSA keys with SHA-1 message digests for its
  * digital signatures.  The choice of RSA is due to its higher
