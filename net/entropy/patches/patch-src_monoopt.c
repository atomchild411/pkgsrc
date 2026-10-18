$NetBSD$

IRIX <sys/types.h> defines cnt_t and index_t.

--- src/monoopt.c.orig
+++ src/monoopt.c
@@ -51,6 +51,8 @@
 
 static const char rotor[4] = {'|', '/', '-', '\\'};
 
+/* IRIX's <sys/types.h> has an index_t (short): rename this one. */
+#define index_t monoopt_index_t
 typedef struct index_s {
 	uint8_t sha1[SHA1SIZE];
 	time_t atime;
