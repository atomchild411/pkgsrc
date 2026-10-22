$NetBSD$

IRIX: <unistd.h> declares environ as char **.

--- env.c.orig
+++ env.c
@@ -132,7 +132,7 @@
 	addnode(env, "USER", target->pw_name);
 
 	if (rule->options & KEEPENV) {
-                #ifndef linux
+                #if !defined(linux) && !defined(__sgi)
 		extern const char **environ;
                 #endif
 
