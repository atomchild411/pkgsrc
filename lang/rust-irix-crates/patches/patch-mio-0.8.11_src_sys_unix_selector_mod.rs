$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2.

--- mio-0.8.11/src/sys/unix/selector/mod.rs.orig
+++ mio-0.8.11/src/sys/unix/selector/mod.rs
@@ -23,19 +23,21 @@ pub(crate) use self::epoll::{event, Event, Events, Selector};
 #[cfg(any(
     mio_unsupported_force_poll_poll,
     target_os = "solaris",
-    target_os = "vita"
+    target_os = "vita",
+    target_os = "irix"
 ))]
 mod poll;
 
 #[cfg(any(
     mio_unsupported_force_poll_poll,
     target_os = "solaris",
-    target_os = "vita"
+    target_os = "vita",
+    target_os = "irix"
 ))]
 pub(crate) use self::poll::{event, Event, Events, Selector};
 
 cfg_io_source! {
-    #[cfg(any(mio_unsupported_force_poll_poll, target_os = "solaris", target_os = "vita"))]
+    #[cfg(any(mio_unsupported_force_poll_poll, target_os = "solaris", target_os = "vita", target_os = "irix"))]
     pub(crate) use self::poll::IoSourceState;
 }
 
