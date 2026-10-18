$NetBSD: patch-src_cache.cc,v 1.1 2017/09/15 22:18:00 ast Exp $

* Compile with pre-2016/12/16 v1.36 dirent.h on NetBSD
* IRIX: scandir() takes the callbacks without const (pre-POSIX 2008)

--- src/cache.cc.orig
+++ src/cache.cc
@@ -19,6 +19,8 @@
  *   Boston, MA 02110-1301 USA.                                            *
  ***************************************************************************/
 
+#include "config.h"
+
 #include "cache.h"
 #include "output.h"
 
@@ -86,9 +88,17 @@
 
 // I feel so bad...
 static const char *cache_directory;
+#if SCANDIR_COMPAR_USES_CONST_VOID_POINTER
+static int agesort(const void *a, const void *b) {
+	std::string A = string(cache_directory) + "/"
+                               + ((const struct dirent *)a)->d_name;
+	std::string B = string(cache_directory) + "/"
+                               + ((const struct dirent *)b)->d_name;
+#else
 static int agesort(const struct dirent ** a, const struct dirent **b) {
 	std::string A = string(cache_directory) + "/" + (*a)->d_name;
 	std::string B = string(cache_directory) + "/" + (*b)->d_name;
+#endif
 
 	struct stat bufa, bufb;
 	if (stat(A.c_str(), &bufa) != 0) return 0;
@@ -110,7 +120,14 @@
 void limit_cachesize(const char *cache, int entries) {
 	struct dirent **namelist;
 	cache_directory = cache;
+#ifdef __sgi
+	// IRIX's scandir() predates POSIX 2008: same callbacks, without const.
+	int n = scandir(cache, &namelist,
+	    reinterpret_cast<int (*)(struct dirent *)>(agefilter),
+	    reinterpret_cast<int (*)(struct dirent **, struct dirent **)>(agesort));
+#else
 	int n = scandir(cache, &namelist, agefilter, agesort);
+#endif
 	if (n < 0) {
 		return;
 	} else {
