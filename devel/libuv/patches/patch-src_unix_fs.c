$NetBSD$

Fix portability on NetBSD.
Apply MacPorts patch-libuv-legacy.diff for pre-10.7 platforms.

IRIX: statfs() is the 4-argument SVR3 call; use statvfs() as on Solaris. No futimens(): uv_fs_copyfile sets the times by path.

--- src/unix/fs.c.orig
+++ src/unix/fs.c
@@ -77,6 +77,7 @@
       defined(__MVS__)    || \
       defined(__NetBSD__) || \
       defined(__HAIKU__)  || \
+      defined(__sgi)      || \
       defined(__QNX__)
 # include <sys/statvfs.h>
 #else
@@ -678,6 +679,7 @@ static int uv__fs_statfs(uv_fs_t* req) {
     defined(__MVS__)    || \
     defined(__NetBSD__) || \
     defined(__HAIKU__)  || \
+    defined(__sgi)      || \
     defined(__QNX__)
   struct statvfs buf;
 
@@ -700,6 +702,7 @@ static int uv__fs_statfs(uv_fs_t* req) {
     defined(__OpenBSD__)  || \
     defined(__NetBSD__)   || \
     defined(__HAIKU__)    || \
+    defined(__sgi)        || \
     defined(__QNX__)
   stat_fs->f_type = 0;  /* f_type is not supported. */
 #else
@@ -1073,7 +1076,7 @@ static ssize_t uv__fs_sendfile(uv_fs_t* req) {
     return -1;
   }
 /* sendfile() on iOS(arm64) will throw SIGSYS signal cause crash. */
-#elif (defined(__APPLE__) && !TARGET_OS_IPHONE)                               \
+#elif (defined(__APPLE__) && MAC_OS_X_VERSION_MAX_ALLOWED >= 1050 && !TARGET_OS_IPHONE) \
     || defined(__DragonFly__)                                                 \
     || defined(__FreeBSD__)
   {
@@ -1324,10 +1327,25 @@ static ssize_t uv__fs_copyfile(uv_fs_t* req) {
   times[1] = src_statsbuf.st_mtim;
 #endif
 
+#if defined(__sgi)
+  /* IRIX has no futimens(): set the times by path. */
+  {
+    struct timeval tv[2];
+    tv[0].tv_sec = times[0].tv_sec;
+    tv[0].tv_usec = times[0].tv_nsec / 1000;
+    tv[1].tv_sec = times[1].tv_sec;
+    tv[1].tv_usec = times[1].tv_nsec / 1000;
+    if (utimes(req->new_path, tv) == -1) {
+      err = UV__ERR(errno);
+      goto out;
+    }
+  }
+#else
   if (futimens(dstfd, times) == -1) {
     err = UV__ERR(errno);
     goto out;
   }
+#endif
 
   /*
    * Change the ownership and permissions of the destination file to match the
@@ -1444,7 +1462,7 @@ static void uv__to_stat(struct stat* src, uv_stat_t* dst) {
   dst->st_blksize = src->st_blksize;
   dst->st_blocks = src->st_blocks;
 
-#if defined(__APPLE__)
+#if defined(__APPLE__) || defined(__NetBSD__)
   dst->st_atim.tv_sec = src->st_atimespec.tv_sec;
   dst->st_atim.tv_nsec = src->st_atimespec.tv_nsec;
   dst->st_mtim.tv_sec = src->st_mtimespec.tv_sec;
@@ -1471,7 +1489,6 @@ static void uv__to_stat(struct stat* src, uv_stat_t* dst) {
     defined(__DragonFly__)   || \
     defined(__FreeBSD__)     || \
     defined(__OpenBSD__)     || \
-    defined(__NetBSD__)      || \
     defined(_GNU_SOURCE)     || \
     defined(_BSD_SOURCE)     || \
     defined(_SVID_SOURCE)    || \
@@ -1483,8 +1500,7 @@ static void uv__to_stat(struct stat* src, uv_stat_t* dst) {
   dst->st_mtim.tv_nsec = src->st_mtim.tv_nsec;
   dst->st_ctim.tv_sec = src->st_ctim.tv_sec;
   dst->st_ctim.tv_nsec = src->st_ctim.tv_nsec;
-# if defined(__FreeBSD__)    || \
-     defined(__NetBSD__)
+# if defined(__FreeBSD__)
   dst->st_birthtim.tv_sec = src->st_birthtim.tv_sec;
   dst->st_birthtim.tv_nsec = src->st_birthtim.tv_nsec;
   dst->st_flags = src->st_flags;
