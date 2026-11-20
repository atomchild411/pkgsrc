$NetBSD$

CVE-2026-121481: buffer overflow in EVP_EncodeBlock() for lengths whose
base64 encoding does not fit in an int. Backport of the guards in
https://github.com/openssl/openssl/pull/33652 (head ad8169a9bb).

--- crypto/http/http_client.c.orig
+++ crypto/http/http_client.c
@@ -1431,7 +1431,8 @@
     size_t outl;
     char *out;
 
-    if (len > INT_MAX)
+    /* Ensure the base64 output length does not overflow. */
+    if (len > (INT_MAX / 4) * 3)
         return 0;
     /* Calculate size of encoded data */
     outl = (len / 3);
