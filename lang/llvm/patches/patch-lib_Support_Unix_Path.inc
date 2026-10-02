$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Build LLVM, clang and lld to run on IRIX

--- lib/Support/Unix/Path.inc.orig
+++ lib/Support/Unix/Path.inc
@@ -108,7 +108,7 @@ typedef uint_t uint;
 #endif
 
 #if defined(__NetBSD__) || defined(__DragonFly__) || defined(__GNU__) ||       \
-    defined(__MVS__)
+    defined(__MVS__) || defined(__sgi)
 #define STATVFS_F_FLAG(vfs) (vfs).f_flag
 #else
 #define STATVFS_F_FLAG(vfs) (vfs).f_flags
@@ -125,7 +125,7 @@ const file_t kInvalidFile = -1;
 #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) ||     \
     defined(__FreeBSD_kernel__) || defined(__linux__) ||                       \
     defined(__CYGWIN__) || defined(__DragonFly__) || defined(_AIX) ||          \
-    defined(__GNU__) ||                                                        \
+    defined(__GNU__) || defined(__sgi) ||                                      \
     (defined(__sun__) && defined(__svr4__) || defined(__HAIKU__)) ||           \
     defined(__managarm__)
 static int test_dir(char ret[PATH_MAX], const char *dir, const char *bin) {
@@ -282,7 +282,8 @@ std::string getMainExecutable(const char *argv0, void *MainAddr) {
   // Fall back to the classical detection.
   if (getprogpath(exe_path, argv0))
     return exe_path;
-#elif defined(__OpenBSD__) || defined(__HAIKU__)
+#elif defined(__OpenBSD__) || defined(__HAIKU__) || defined(__sgi)
+  // IRIX: no dladdr, and its /proc gives no path.
   char exe_path[PATH_MAX];
   // argv[0] only
   if (getprogpath(exe_path, argv0) != NULL)
@@ -511,7 +512,7 @@ static bool is_local_impl(struct STATVFS &Vfs) {
 #elif defined(__HAIKU__)
   // Haiku doesn't expose this information.
   return false;
-#elif defined(__sun)
+#elif defined(__sun) || defined(__sgi)
   // statvfs::f_basetype contains a null-terminated FSType name of the mounted
   // target
   StringRef fstype(Vfs.f_basetype);
