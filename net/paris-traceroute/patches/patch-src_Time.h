$NetBSD$

IRIX <time.h> uses the __TIME_H__ guard too.

--- src/Time.h.orig
+++ src/Time.h
@@ -1,5 +1,5 @@
-#ifndef __TIME_H__
-#define __TIME_H__
+#ifndef PT_TIME_H
+#define PT_TIME_H
 
 #include <sys/time.h>
 
