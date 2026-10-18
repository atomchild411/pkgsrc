$NetBSD$

IRIX: no tm_gmtoff, as on Solaris.

--- src/lua/lua_task.c.orig
+++ src/lua/lua_task.c
@@ -6113,7 +6113,7 @@
 
 				tt = tim;
 				rspamd_localtime(tt, &t);
-#if !defined(__sun)
+#if !defined(__sun) && !defined(__sgi)
 				t.tm_gmtoff = 0;
 #endif
 				t.tm_isdst = 0;
@@ -6135,7 +6135,7 @@
 				if (err == NULL) {
 					if (!gmt) {
 						rspamd_localtime(tt, &t);
-#if !defined(__sun)
+#if !defined(__sun) && !defined(__sgi)
 						t.tm_gmtoff = 0;
 #endif
 						t.tm_isdst = 0;
