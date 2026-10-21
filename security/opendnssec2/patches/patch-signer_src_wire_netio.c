$NetBSD$

IRIX <time.h> defines a timeval_to_timespec() macro.

--- signer/src/wire/netio.c.orig
+++ signer/src/wire/netio.c
@@ -95,6 +95,7 @@
  * Convert timeval to timespec.
  *
  */
+#undef timeval_to_timespec	/* IRIX <time.h> has a macro of that name */
 static void
 timeval_to_timespec(struct timespec* left, const struct timeval* right)
 {
