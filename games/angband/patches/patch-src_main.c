$NetBSD$

With MSYS2_ENCODING_WORKAROUND the front ends convert UTF-8 themselves,
whatever the locale: do not require a UTF-8 locale then (IRIX has none).

--- src/main.c.orig
+++ src/main.c
@@ -481,9 +481,11 @@
 		ANGBAND_SYS = mstr;
 #if !defined(WINDOWS) && !defined(DJGPP)
 	if (setlocale(LC_CTYPE, "")) {
+#ifndef MSYS2_ENCODING_WORKAROUND
 		/* Require UTF-8 */
 		if (!streq(nl_langinfo(CODESET), "UTF-8"))
 			quit("Angband requires UTF-8 support");
+#endif
 	}
 #endif
 
