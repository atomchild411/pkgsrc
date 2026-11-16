$NetBSD$

The sintable and radarang checks CRC the tables' raw bytes against
little-endian values, so they always failed on big-endian CPUs ("Calculation
of sintable yielded unexpected results"): CRC a little-endian copy there.

--- jfbuild/src/engine.c.orig
+++ jfbuild/src/engine.c
@@ -4912,6 +4912,25 @@
 	}
 }
 
+/*
+ * CRC of a table of shorts in little-endian byte order: the expected values
+ * below were taken on little-endian machines, so a big-endian one has to
+ * swap before checking.
+ */
+static unsigned int crc32le16(const short *tab, int n)
+{
+#if B_BIG_ENDIAN
+	unsigned short le[2048];
+	int i;
+
+	if (n > 2048) return 0;
+	for (i = 0; i < n; i++) le[i] = B_LITTLE16((unsigned short)tab[i]);
+	return crc32once((unsigned char *)le, (unsigned int)n * 2);
+#else
+	return crc32once((unsigned char *)tab, (unsigned int)n * 2);
+#endif
+}
+
 static int loadtables(void)
 {
 	int i;
@@ -4927,11 +4946,11 @@
     }
 	calcbritable();
 
-    if (crc32once((unsigned char *)sintable, sizeof(sintable)) != 0xee1e7aba) {
+    if (crc32le16(sintable, 2048) != 0xee1e7aba) {
         engineerrstr = "Calculation of sintable yielded unexpected results.";
         return 1;
     }
-    if (crc32once((unsigned char *)radarang, sizeof(radarang)/2) != 0xee893d92) {
+    if (crc32le16(radarang, 640) != 0xee893d92) {
         engineerrstr = "Calculation of radarang yielded unexpected results.";
         return 1;
     }
