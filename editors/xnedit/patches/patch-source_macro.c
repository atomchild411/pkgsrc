$NetBSD$

NO_XMIM (set for IRIX) builds: status is used either way.

--- source/macro.c.orig
+++ source/macro.c
@@ -1569,9 +1569,7 @@
     char chars[512], *charList[1], *outStr, *outPtr;
     KeySym keysym;
     int i, nChars, nParams, length, nameLength;
-#ifndef NO_XMIM
-    int status;
-#endif
+    int status; /* TextLookupString() sets it with NO_XMIM too */
     
     if (isIgnoredAction(actionName) || isRedundantAction(actionName) ||
 	    isMouseAction(actionName))
