$NetBSD$

NO_XMIM (set for IRIX) builds: status is used either way.

--- source/text.c.orig
+++ source/text.c
@@ -2548,9 +2548,8 @@
 
 #ifdef NO_XMIM
     static XComposeStatus compose = {NULL, 0};
-#else
-    int status;
 #endif
+    int status; /* TextLookupString() sets it with NO_XMIM too */
     XKeyEvent *e = &event->xkey;   
     char chars[512];
     KeySym keysym;
