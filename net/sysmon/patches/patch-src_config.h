$NetBSD$

IRIX: ncurses comes from pkgsrc (buildlink), not /usr/local; no libl for yywrap.

--- src/config.h.orig
+++ src/config.h
@@ -72,11 +72,7 @@
 #endif /* HAVE_LIBNCURSES */
 
 #ifdef NICEINTERFACE
-#ifdef sgi
-#include "/usr/local/include/ncurses.h"
-#else
-#include <curses.h>
-#endif /* sgi */
+#include <curses.h>	/* pkgsrc's ncurses on IRIX too, through buildlink */
 #endif /* NICEINTERFACE */
 
 #ifdef HAVE_NET_SNMP_VERSION_H
