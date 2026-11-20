$NetBSD$

CVE-2026-121481: buffer overflow in EVP_EncodeBlock() for lengths whose
base64 encoding does not fit in an int. Backport of the guards in
https://github.com/openssl/openssl/pull/33652 (head ad8169a9bb).

--- crypto/evp/encode.c.orig
+++ crypto/evp/encode.c
@@ -258,6 +258,19 @@
 
 int EVP_EncodeBlock(unsigned char *t, const unsigned char *f, int dlen)
 {
+    OPENSSL_assert(dlen >= 0);
+    /*
+     * Base64 expands 3 input bytes to 4 output bytes, therefore
+     * 4 * ceil(dlen / 3) fits in an int if and only if
+     * dlen <= 3 * floor(INT_MAX / 4).
+     */
+    OPENSSL_assert(dlen <= (INT_MAX / 4) * 3);
+
+    if (dlen == 0) {
+        *t = '\0';
+        return 0;
+    }
+
     return evp_encodeblock_int(NULL, t, f, dlen);
 }
 
@@ -482,6 +495,9 @@
 
 int EVP_DecodeBlock(unsigned char *t, const unsigned char *f, int n)
 {
+    if (n <= 0)
+        return n == 0 ? 0 : -1;
+
     return evp_decodeblock_int(NULL, t, f, n, 0);
 }
 
