$NetBSD$

An empty name, without d_namlen (not in IRIX's struct dirent).

--- check_mqueue.c.orig
+++ check_mqueue.c
@@ -90,7 +90,7 @@
 			err(NAGIOS_UNKNOWN, "opendir %s failed", queuedir);
 
 		while ((dp = readdir(queue)) != NULL) {
-			if (dp->d_namlen < 1)
+			if (dp->d_name[0] == '\0')
 				continue;
 			if (dp->d_name[0] == 'd')
 				queuelen++;
