$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2.

--- mio-1.2.3/src/sys/unix/mod.rs.orig
+++ mio-1.2.3/src/sys/unix/mod.rs
@@ -52,6 +52,7 @@ cfg_os_poll! {
         target_os = "hermit",
         target_os = "hurd",
         target_os = "nto",
+        target_os = "irix",
         target_os = "vita",
         target_os = "cygwin",
         target_os = "wasi",
@@ -110,6 +111,7 @@ cfg_os_poll! {
         target_os = "haiku",
         target_os = "hurd",
         target_os = "nto",
+        target_os = "irix",
         target_os = "redox",
         all(mio_unsupported_force_poll_poll, target_os = "solaris"),
         target_os = "vita",
@@ -162,6 +164,7 @@ cfg_os_poll! {
             target_os = "hurd",
             target_os = "netbsd",
             target_os = "nto",
+            target_os = "irix",
             target_os = "openbsd",
             target_os = "redox",
             all(mio_unsupported_force_poll_poll, target_os = "solaris"),
