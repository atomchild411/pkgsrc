$NetBSD$

IRIX: no d_type, st_mtimespec or tm_gmtoff.

--- lib/the_Foundation/src/fileinfo.c.orig
+++ lib/the_Foundation/src/fileinfo.c
@@ -80,7 +80,7 @@
 typedef struct stat iStatBuf;
 #endif
 
-#if defined (iPlatformLinux) || defined (iPlatformMsys) || defined (iPlatformCygwin) || defined (iPlatformHaiku)
+#if defined (iPlatformLinux) || defined (iPlatformMsys) || defined (iPlatformCygwin) || defined (iPlatformHaiku) || defined (__sgi)
 #   define st_mtimespec st_mtim
 #endif
 
@@ -160,7 +160,10 @@
     if (access_(cstr_String(d->path), W_OK) == 0) {
         d->flags |= writable_FileInfoFlag;
     }
-#if defined (iPlatformHaiku)
+#if defined (__sgi) /* IRIX: no d_type */
+    iStatBuf s;
+    if (stat(cstr_String(d->path), &s) == 0 && S_ISDIR(s.st_mode)) {
+#elif defined (iPlatformHaiku)
     iStatBuf s;
     stat(ent->d_name, &s);
     if (S_ISDIR(s.st_mode)) {
