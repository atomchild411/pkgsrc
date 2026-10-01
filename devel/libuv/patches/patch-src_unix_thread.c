$NetBSD$

IRIX: no pthread_condattr_setclock() (wait relatively, as on macOS: our toolchain provides pthread_cond_timedwait_relative_np) and no thread names.

--- src/unix/thread.c.orig
+++ src/unix/thread.c
@@ -727,7 +727,7 @@ int uv_sem_trywait(uv_sem_t* sem) {
 #endif /* defined(__APPLE__) && defined(__MACH__) */
 
 
-#if defined(__APPLE__) && defined(__MACH__) || defined(__MVS__)
+#if defined(__APPLE__) && defined(__MACH__) || defined(__MVS__) || defined(__sgi)
 
 int uv_cond_init(uv_cond_t* cond) {
   return UV__ERR(pthread_cond_init(cond, NULL));
@@ -845,7 +845,8 @@ int uv_cond_timedwait(uv_cond_t* cond, uv_mutex_t* mutex, uint64_t timeout) {
   struct timeval tv;
 #endif
 
-#if defined(__APPLE__) && defined(__MACH__)
+#if defined(__APPLE__) && defined(__MACH__) || defined(__sgi)
+  /* (IRIX: no pthread_condattr_setclock(); the relative wait is ours.) */
   ts.tv_sec = timeout / NANOSEC;
   ts.tv_nsec = timeout % NANOSEC;
   r = pthread_cond_timedwait_relative_np(cond, mutex, &ts);
@@ -895,7 +896,7 @@ void uv_key_set(uv_key_t* key, void* value) {
     abort();
 }
 
-#if defined(_AIX) || defined(__MVS__) || defined(__PASE__)
+#if defined(_AIX) || defined(__MVS__) || defined(__PASE__) || defined(__sgi)
 int uv__thread_setname(const char* name) {
   return UV_ENOSYS;
 }
@@ -936,7 +937,8 @@ int uv__thread_setname(const char* name) {
 #if (defined(__ANDROID_API__) && __ANDROID_API__ < 26) || \
     defined(_AIX) || \
     defined(__MVS__) || \
-    defined(__PASE__)
+    defined(__PASE__) || \
+    defined(__sgi)
 int uv__thread_getname(uv_thread_t* tid, char* name, size_t size) {
   return UV_ENOSYS;
 }
