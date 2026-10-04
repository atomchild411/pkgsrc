$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2.

--- mio-0.8.11/src/sys/unix/waker.rs.orig
+++ mio-0.8.11/src/sys/unix/waker.rs
@@ -10,7 +10,7 @@
             target_os = "watchos",
         )
     )),
-    not(any(target_os = "solaris", target_os = "vita")),
+    not(any(target_os = "solaris", target_os = "vita", target_os = "irix")),
 ))]
 mod fdbased {
     #[cfg(all(
@@ -21,6 +21,7 @@ mod fdbased {
     #[cfg(any(
         mio_unsupported_force_waker_pipe,
         target_os = "aix",
+        target_os = "irix",
         target_os = "dragonfly",
         target_os = "illumos",
         target_os = "netbsd",
@@ -63,7 +64,7 @@ mod fdbased {
             target_os = "watchos",
         )
     )),
-    not(any(target_os = "solaris", target_os = "vita")),
+    not(any(target_os = "solaris", target_os = "vita", target_os = "irix")),
 ))]
 pub use self::fdbased::Waker;
 
@@ -202,6 +203,7 @@ pub use self::kqueue::Waker;
 #[cfg(any(
     mio_unsupported_force_waker_pipe,
     target_os = "aix",
+    target_os = "irix",
     target_os = "dragonfly",
     target_os = "illumos",
     target_os = "netbsd",
@@ -209,6 +211,7 @@ pub use self::kqueue::Waker;
     target_os = "redox",
     target_os = "solaris",
     target_os = "vita",
+    target_os = "irix",
 ))]
 mod pipe {
     use crate::sys::unix::pipe;
@@ -257,7 +260,8 @@ mod pipe {
         #[cfg(any(
             mio_unsupported_force_poll_poll,
             target_os = "solaris",
-            target_os = "vita"
+            target_os = "vita",
+            target_os = "irix"
         ))]
         pub fn ack_and_reset(&self) {
             self.empty();
@@ -289,6 +293,7 @@ mod pipe {
         any(
             mio_unsupported_force_waker_pipe,
             target_os = "aix",
+            target_os = "irix",
             target_os = "dragonfly",
             target_os = "illumos",
             target_os = "netbsd",
@@ -298,13 +303,15 @@ mod pipe {
     ),
     target_os = "solaris",
     target_os = "vita",
+    target_os = "irix",
 ))]
 pub(crate) use self::pipe::WakerInternal;
 
 #[cfg(any(
     mio_unsupported_force_poll_poll,
     target_os = "solaris",
-    target_os = "vita"
+    target_os = "vita",
+    target_os = "irix"
 ))]
 mod poll {
     use crate::sys::Selector;
@@ -334,6 +341,7 @@ mod poll {
 #[cfg(any(
     mio_unsupported_force_poll_poll,
     target_os = "solaris",
-    target_os = "vita"
+    target_os = "vita",
+    target_os = "irix"
 ))]
 pub use self::poll::Waker;
