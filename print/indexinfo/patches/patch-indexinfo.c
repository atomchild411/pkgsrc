$NetBSD$

IRIX: no d_namlen in struct dirent.

--- indexinfo.c.orig
+++ indexinfo.c
@@ -211,6 +211,9 @@
 #ifdef __linux__
 		if (_D_EXACT_NAMLEN(dp) < 5)
 			continue;
+#elif defined(__sgi)	/* no d_namlen */
+		if (strlen(dp->d_name) < 5)
+			continue;
 #else
 		if (dp->d_namlen < 5)
 			continue;
