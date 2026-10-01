$NetBSD$

IRIX: clang's IRIX <dlfcn.h> declares dladdr (over rld, as dladdr(3C)
describes) and says so with __CLANG_IRIX_DLADDR; a second, static one
here is then a conflicting declaration.

--- crypto/dso/dso_dlfcn.c.orig
+++ crypto/dso/dso_dlfcn.c
@@ -271,7 +271,7 @@
     return translated;
 }
 
-#ifdef __sgi
+#if defined(__sgi) && !defined(__CLANG_IRIX_DLADDR)
 /*-
 This is a quote from IRIX manual for dladdr(3c):
 
