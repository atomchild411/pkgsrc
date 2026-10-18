$NetBSD$

IRIX struct tm has no tm_zone.

--- lex.l.orig
+++ lex.l
@@ -304,7 +304,7 @@
     tm.tm_min = n->n[4];
     tm.tm_sec = n->n[5];
     tm.tm_isdst = 0;
-#if !defined(__CYGWIN__) && !defined(__sun)
+#if !defined(__CYGWIN__) && !defined(__sun) && !defined(__sgi)
     tm.tm_zone = 0;
 #endif
     d = mktime(&tm);
