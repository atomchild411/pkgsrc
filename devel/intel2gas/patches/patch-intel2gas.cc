$NetBSD$

In C++, strchr() and strstr() on a const string return const char *.

--- intel2gas.cc.orig
+++ intel2gas.cc
@@ -448,7 +448,7 @@
 {
   match.at = NULL;
   for (int c=0; c<comments; c++) {
-    char *pos = strstr(source, comment[c].src);
+    char *pos = (char *)strstr(source, comment[c].src);
     if (!match.at || (pos && pos < match.at)) {
       match.at = pos;
       match.data = &comment[c];
