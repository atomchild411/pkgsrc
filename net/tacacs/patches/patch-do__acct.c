$NetBSD$

IRIX: SVR4 struct utmp has no ut_host, as on Solaris.

--- do_acct.c.orig
+++ do_acct.c
@@ -230,7 +230,7 @@
     else
 	memcpy(entry.ut_name, name, sizeof(entry.ut_name));
 
-#ifndef SOLARIS
+#if !defined(SOLARIS) && !defined(__sgi) /* SVR4 utmp: no ut_host */
     if (strlen(host) < sizeof entry.ut_host)
 	strcpy(entry.ut_host, host);
     else
