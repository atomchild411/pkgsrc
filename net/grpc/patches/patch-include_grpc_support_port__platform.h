$NetBSD$

IRIX 6.5: a POSIX platform, as Solaris is.

--- include/grpc/support/port_platform.h.orig
+++ include/grpc/support/port_platform.h
@@ -378,6 +378,26 @@
 #else /* _LP64 */
 #define GPR_ARCH_32 1
 #endif /* _LP64 */
+#elif defined(__sgi)
+#define GPR_PLATFORM_STRING "irix"
+#define GPR_IRIX 1
+#define GPR_CPU_POSIX 1
+#define GPR_GCC_ATOMIC 1
+#define GPR_POSIX_LOG 1
+#define GPR_POSIX_ENV 1
+#define GPR_POSIX_TMPFILE 1
+#define GPR_POSIX_STAT 1
+#define GPR_POSIX_STRING 1
+#define GPR_POSIX_SUBPROCESS 1
+#define GPR_POSIX_SYNC 1
+#define GPR_POSIX_TIME 1
+#define GPR_HAS_PTHREAD_H 1
+#define GPR_GETPID_IN_UNISTD_H 1
+#ifdef _LP64
+#define GPR_ARCH_64 1
+#else /* _LP64 */
+#define GPR_ARCH_32 1
+#endif /* _LP64 */
 #elif defined(_AIX)
 #define GPR_PLATFORM_STRING "aix"
 #ifndef _ALL_SOURCE
