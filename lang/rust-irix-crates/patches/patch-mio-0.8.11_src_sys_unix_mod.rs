$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2. Cargo.toml: only the dependencies IRIX builds use.

--- mio-0.8.11/src/sys/unix/mod.rs.orig
+++ mio-0.8.11/src/sys/unix/mod.rs
@@ -35,7 +35,7 @@ cfg_os_poll! {
 
     cfg_io_source! {
         // Both `kqueue` and `epoll` don't need to hold any user space state.
-        #[cfg(not(any(mio_unsupported_force_poll_poll, target_os = "solaris", target_os = "vita")))]
+        #[cfg(not(any(mio_unsupported_force_poll_poll, target_os = "solaris", target_os = "vita", target_os = "irix")))]
         mod stateless_io_source {
             use std::io;
             use std::os::unix::io::RawFd;
@@ -88,10 +88,10 @@ cfg_os_poll! {
             }
         }
 
-        #[cfg(not(any(mio_unsupported_force_poll_poll, target_os = "solaris",target_os = "vita")))]
+        #[cfg(not(any(mio_unsupported_force_poll_poll, target_os = "solaris",target_os = "vita", target_os = "irix")))]
         pub(crate) use self::stateless_io_source::IoSourceState;
 
-        #[cfg(any(mio_unsupported_force_poll_poll, target_os = "solaris", target_os = "vita"))]
+        #[cfg(any(mio_unsupported_force_poll_poll, target_os = "solaris", target_os = "vita", target_os = "irix"))]
         pub(crate) use self::selector::IoSourceState;
     }
 
@@ -101,6 +101,7 @@ cfg_os_poll! {
         // For the `Waker` type based on a pipe.
         mio_unsupported_force_waker_pipe,
         target_os = "aix",
+        target_os = "irix",
         target_os = "dragonfly",
         target_os = "illumos",
         target_os = "netbsd",
@@ -108,6 +109,7 @@ cfg_os_poll! {
         target_os = "redox",
         target_os = "solaris",
         target_os = "vita",
+        target_os = "irix",
     ))]
     pub(crate) mod pipe;
 }
