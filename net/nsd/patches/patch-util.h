$NetBSD$

IRIX <time.h> defines a timeval_to_timespec macro (in SGI mode).

--- util.h.orig
+++ util.h
@@ -315,6 +315,7 @@
 void timespec_add(struct timespec *left, const struct timespec *right);
 void timespec_subtract(struct timespec *left, const struct timespec *right);
 
+#undef timeval_to_timespec /* IRIX <time.h> has a macro of this name */
 static inline void
 timeval_to_timespec(struct timespec *left,
 		    const struct timeval *right)
