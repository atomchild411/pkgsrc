$NetBSD$

IRIX has the POSIX.1e capability calls (cap_init, cap_clear, cap_set_proc,
cap_free in libc), as Linux does.

--- src/daemon/caps.c.orig
+++ src/daemon/caps.c
@@ -78,7 +78,7 @@
 
 void pa_drop_caps(void) {
 #ifdef HAVE_SYS_CAPABILITY_H
-#if defined(__linux__)
+#if defined(__linux__) || defined(__sgi)
     cap_t caps;
     pa_assert_se(caps = cap_init());
     pa_assert_se(cap_clear(caps) == 0);
