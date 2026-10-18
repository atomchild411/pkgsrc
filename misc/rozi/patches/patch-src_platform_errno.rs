$NetBSD$

IRIX keeps errno at __oserror().

--- src/platform/errno.rs.orig
+++ src/platform/errno.rs
@@ -51,6 +51,12 @@
     unsafe { libc::___errno() }
 }
 
+/// Address of the calling thread's `errno`. See the Linux arm for safety.
+#[cfg(target_os = "irix")]
+pub(crate) unsafe fn errno_slot() -> *mut libc::c_int {
+    unsafe { libc::__oserror() }
+}
+
 #[cfg(not(any(
     target_os = "linux",
     target_os = "hurd",
@@ -66,7 +72,8 @@
     target_os = "freebsd",
     target_os = "dragonfly",
     target_os = "solaris",
-    target_os = "illumos"
+    target_os = "illumos",
+    target_os = "irix"
 )))]
 compile_error!(
     "rozi does not know how this target exposes `errno`. Add it to one of the arms in \
