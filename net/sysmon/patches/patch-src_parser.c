$NetBSD$

IRIX: ncurses comes from pkgsrc (buildlink), not /usr/local; no libl for yywrap.

--- src/parser.c.orig
+++ src/parser.c
@@ -4925,3 +4925,7 @@
 	}
 }
 
+#ifdef __sgi	/* no libl in the IRIX sysroot (configure found no yywrap) */
+int yywrap(void) { return 1; }
+#endif
+
