$NetBSD$

IRIX port (pthreads, IPv4); NSPR dropped its old one.

--- nspr/pr/include/md/_pth.h.orig
+++ nspr/pr/include/md/_pth.h
@@ -64,7 +64,7 @@
     || defined(LINUX) || defined(__GNU__) || defined(__GLIBC__) \
     || defined(FREEBSD) || defined(NETBSD) || defined(OPENBSD) \
     || defined(NTO) || defined(DARWIN) \
-    || defined(RISCOS)
+    || defined(RISCOS) || defined(IRIX)
 #define _PT_PTHREAD_INVALIDATE_THR_HANDLE(t)  (t) = 0
 #define _PT_PTHREAD_THR_HANDLE_IS_INVALID(t)  (t) == 0
 #define _PT_PTHREAD_COPY_THR_HANDLE(st, dt)   (dt) = (st)
@@ -103,7 +103,7 @@
 #define PT_PRIO_MIN            DEFAULT_PRIO
 #define PT_PRIO_MAX            DEFAULT_PRIO
 #elif defined(LINUX) || defined(__GNU__) || defined(__GLIBC__) \
-    || defined(FREEBSD)
+    || defined(FREEBSD) || defined(IRIX)
 #define PT_PRIO_MIN            sched_get_priority_min(SCHED_OTHER)
 #define PT_PRIO_MAX            sched_get_priority_max(SCHED_OTHER)
 #elif defined(NTO)
@@ -147,7 +147,7 @@
     || defined(LINUX) || defined(__GNU__) || defined(__GLIBC__) \
     || defined(FREEBSD) || defined(NETBSD) || defined(OPENBSD) \
     || defined(NTO) || defined(DARWIN) \
-    || defined(RISCOS)
+    || defined(RISCOS) || defined(IRIX)
 #define _PT_PTHREAD_YIELD()             sched_yield()
 #else
 #error "Need to define _PT_PTHREAD_YIELD for this platform"
