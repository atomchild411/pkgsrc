$NetBSD$

In C++, strchr() and strstr() on a const string return const char *.

--- strhandle.cc.orig
+++ strhandle.cc
@@ -14,7 +14,7 @@
  * Modifies: str */
 char *str_cutat(char *str, char cut)
 {
-    char *pos = strchr(str,cut);
+    char *pos = (char *)strchr(str,cut);
     if (!pos) return NULL;
     *pos = '\0';
     return pos+1;
@@ -24,7 +24,7 @@
 /* Like str_cutat, but the beginning of str is copied to buffer at left */
 char *str_splitat(char const * const str, char *left, char cut)
 {
-    char *pos = strchr(str,cut);
+    char *pos = (char *)strchr(str,cut);
     if (!pos) {
         strcpy(left,str);
         return NULL;
