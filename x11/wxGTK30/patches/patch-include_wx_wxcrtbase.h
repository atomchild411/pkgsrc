$NetBSD$

IRIX 6.5.7 has no _xpg5_wcsftime: use wx's own wcsftime.

--- include/wx/wxcrtbase.h.orig
+++ include/wx/wxcrtbase.h
@@ -592,12 +592,16 @@
         probably be simpler to just always use our own wxCRT_StrftimeW() below
         if it does ever become a problem).
      */
+    /* pkgsrc: IRIX 6.5.7's libc has no _xpg5_wcsftime; leave
+       wxCRT_StrftimeW to wx's own (wxcrt.cpp). */
+#if 0
 #ifdef __cplusplus
     extern "C"
 #endif
     size_t
     _xpg5_wcsftime(wchar_t *, size_t, const wchar_t *, const struct tm * );
     #define wxCRT_StrftimeW _xpg5_wcsftime
+#endif
 #else
     /*
         Assume it's always available under non-Unix systems as this does seem
