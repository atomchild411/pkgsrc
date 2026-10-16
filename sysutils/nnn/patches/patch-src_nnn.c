$NetBSD: patch-src_nnn.c,v 1.7 2024/07/15 22:44:54 sjmulder Exp $

 - dprintf() polyfill for Solaris.
   https://github.com/jarun/nnn/pull/1911
 - Disable large file support on old glibc where unsupported in fts.h.
   https://github.com/jarun/nnn/pull/1910
 - No d_type in struct dirent on IRIX: use the Solaris/Haiku fstatat() path.

--- src/nnn.c.orig
+++ src/nnn.c
@@ -28,13 +28,16 @@
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */
 
-#define _FILE_OFFSET_BITS 64 /* Support large files on 32-bit glibc */
-
 #if defined(__linux__) || defined(MINGW) || defined(__MINGW32__) \
 	|| defined(__MINGW64__) || defined(__CYGWIN__)
 #ifndef _GNU_SOURCE
 #define _GNU_SOURCE
 #endif
+#include <features.h>		/* __GLIBC__ etc */
+/* large file support on 32-bit glibc >= 2.23 where fts.h supports it */
+#if !defined(__GLIBC__) || __GLIBC__ > 2 || __GLIBC_MINOR__ >= 23
+#define _FILE_OFFSET_BITS 64
+#endif
 #if defined(__linux__)
 #include <sys/inotify.h>
 #define LINUX_INOTIFY
@@ -122,6 +125,10 @@
 #define alloca(size) __builtin_alloca(size)
 #endif
 
+#ifdef __sun
+#define NEED_DPRINTF
+#endif
+
 #include "nnn.h"
 #include "dbg.h"
 
@@ -869,6 +876,27 @@ static void notify_fifo(bool force);
 
 /* Functions */
 
+#ifdef NEED_DPRINTF
+static int dprintf(int fd, const char *format, ...)
+{
+	va_list ap;
+	char *s;
+	int len, nwritten;
+
+	va_start(ap, format);
+	len = vasprintf(&s, format, ap);
+	va_end(ap);
+
+	if (len == -1)
+		return -1;
+
+	nwritten = write(fd, s, len);
+	free(s);
+
+	return nwritten;
+}
+#endif
+
 static void sigint_handler(int sig)
 {
 	(void) sig;
@@ -5908,7 +5936,7 @@ static int dentfill(char *path, struct e
 	if (!dp)
 		goto exit;
 
-#if defined(__sun) || defined(__HAIKU__)
+#if defined(__sun) || defined(__HAIKU__) || !defined(DT_UNKNOWN)
 	flags = AT_SYMLINK_NOFOLLOW; /* no d_type */
 #else
 	if (cfg.blkorder || dp->d_type == DT_UNKNOWN) {
@@ -6041,7 +6069,7 @@ static int dentfill(char *path, struct e
 		if ((gtimesecs - sb.st_mtime <= 300) || (gtimesecs - sb.st_ctime <= 300))
 			entflags |= FILE_YOUNG;
 
-#if !(defined(__sun) || defined(__HAIKU__))
+#if !(defined(__sun) || defined(__HAIKU__) || !defined(DT_UNKNOWN))
 		if (!flags && dp->d_type == DT_LNK) {
 			 /* Do not add sizes for links */
 			dentp->mode = (sb.st_mode & ~S_IFMT) | S_IFLNK;
@@ -6093,7 +6121,7 @@ static int dentfill(char *path, struct e
 
 			if (S_ISDIR(sb.st_mode))
 				dentp->flags |= DIR_OR_DIRLNK;
-#if !(defined(__sun) || defined(__HAIKU__)) /* no d_type */
+#if !(defined(__sun) || defined(__HAIKU__) || !defined(DT_UNKNOWN)) /* no d_type */
 		} else if (dp->d_type == DT_DIR || ((dp->d_type == DT_LNK
 			   || dp->d_type == DT_UNKNOWN) && S_ISDIR(sb.st_mode))) {
 			dentp->flags |= DIR_OR_DIRLNK;
