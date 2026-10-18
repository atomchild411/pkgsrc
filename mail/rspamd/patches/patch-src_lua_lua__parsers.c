$NetBSD$

IRIX: no tm_gmtoff, as on Solaris.

--- src/lua/lua_parsers.c.orig
+++ src/lua/lua_parsers.c
@@ -441,7 +441,7 @@
 			struct tm t;
 
 			rspamd_localtime(tt, &t);
-#if !defined(__sun)
+#if !defined(__sun) && !defined(__sgi)
 			t.tm_gmtoff = 0;
 #endif
 			t.tm_isdst = 0;
