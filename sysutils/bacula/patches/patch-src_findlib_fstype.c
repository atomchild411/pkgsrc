$NetBSD: patch-src_findlib_fstype.c,v 1.1 2022/10/06 02:58:17 markd Exp $
HP-UX/IRIX/AIX branch: the missing line continuation; on IRIX fstypeid from statvfs (its statfs is SVR3's).

--- src/findlib/fstype.c.orig
+++ src/findlib/fstype.c
@@ -158,7 +158,7 @@
    struct statvfs st;
 
    if (statvfs(fname, &st) == 0) {
-      return st.f_type;
+      return (((uint64_t)st.f_fsidx.__fsid_val[0])<<32) | st.f_fsidx.__fsid_val[1];
    }
    return 0;
 }
@@ -184,7 +184,7 @@
 }
 
 #elif defined(HAVE_HPUX_OS)                     \
-   || defined(HAVE_IRIX_OS)
+   || defined(HAVE_IRIX_OS)                     \
    || defined(HAVE_AIX_OS)
 
 #include <sys/types.h>
@@ -205,11 +205,20 @@
  */
 static uint64_t fstypeid(char *fname, FF_PKT *ff_pkt)
 {
+#ifdef HAVE_IRIX_OS
+   /* IRIX's statfs is SVR3's (four arguments). */
+   struct statvfs st;
+
+   if (statvfs(fname, &st) == 0) {
+      return st.f_fsid;
+   }
+#else
    struct statfs st;
 
    if (statfs(fname, &st) == 0) {
       return st.f_fsid;
    }
+#endif
    return 0;
 }
 
