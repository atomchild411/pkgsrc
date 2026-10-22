$NetBSD$

IRIX: shadow passwords through getspnam (its <pwd.h> guard is not _PWD_H).

--- socket.c.orig
+++ socket.c
@@ -1243,7 +1243,7 @@
 	bool ret = false;
 	char *passwd = 0;
 
-#ifndef _PWD_H
+#if !defined(_PWD_H) && !defined(__sgi)
 	struct passwd *p;
 #else
 	struct spwd *p;
@@ -1255,7 +1255,7 @@
 	if (seteuid(0) || setegid(0))
 		Panic(0, "\r\ncan't get root uid/gid\r\n");
 
-#ifndef _PWD_H
+#if !defined(_PWD_H) && !defined(__sgi)
 	p = getpwnam_shadow(ppp->pw_name);
 #else
 	p = getspnam(ppp->pw_name);
@@ -1270,7 +1270,7 @@
 		AddStr("\r\ncan't open passwd file\r\n");
 		return false;
 	}
-#ifndef _PWD_H
+#if !defined(_PWD_H) && !defined(__sgi)
 	passwd = crypt(password, p->pw_passwd);
 	ret    = (strcmp(passwd, p->pw_passwd) == 0);
 #else
