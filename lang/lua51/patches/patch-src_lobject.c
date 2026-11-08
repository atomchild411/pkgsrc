$NetBSD$

IRIX: hexadecimal numbers ("0x10") were "malformed": IRIX's strtod reads
C99 hexadecimal numbers only with a binary exponent and converts nothing
for "0x10". Hand the "0x" to the strtoul path, as with a C89 strtod.

--- src/lobject.c.orig
+++ src/lobject.c
@@ -90,6 +90,18 @@
 int luaO_str2d (const char *s, lua_Number *result) {
   char *endptr;
   *result = lua_str2number(s, &endptr);
+#if defined(__sgi)
+  /* IRIX's strtod reads C99 hexadecimal numbers only with a binary
+     exponent ("0x1p4"): for "0x10" it converts nothing. Leave the "0x"
+     to strtoul below, as with a C89 strtod. */
+  {
+    const char *h = s;
+    while (isspace(cast(unsigned char, *h))) h++;
+    if (*h == '-' || *h == '+') h++;
+    if (h[0] == '0' && (h[1] == 'x' || h[1] == 'X') && endptr <= h + 1)
+      endptr = cast(char *, h + 1);
+  }
+#endif
   if (endptr == s) return 0;  /* conversion failed */
   if (*endptr == 'x' || *endptr == 'X')  /* maybe an hexadecimal constant? */
     *result = cast_num(strtoul(s, &endptr, 16));
