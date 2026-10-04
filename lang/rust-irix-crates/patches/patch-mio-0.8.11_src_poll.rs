$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2.

--- mio-0.8.11/src/poll.rs.orig
+++ mio-0.8.11/src/poll.rs
@@ -1,7 +1,7 @@
 #[cfg(all(
     unix,
     not(mio_unsupported_force_poll_poll),
-    not(any(target_os = "solaris", target_os = "vita"))
+    not(any(target_os = "solaris", target_os = "vita", target_os = "irix"))
 ))]
 use std::os::unix::io::{AsRawFd, RawFd};
 #[cfg(all(debug_assertions, not(target_os = "wasi")))]
@@ -430,7 +430,7 @@ impl Poll {
 #[cfg(all(
     unix,
     not(mio_unsupported_force_poll_poll),
-    not(any(target_os = "solaris", target_os = "vita"))
+    not(any(target_os = "solaris", target_os = "vita", target_os = "irix"))
 ))]
 impl AsRawFd for Poll {
     fn as_raw_fd(&self) -> RawFd {
@@ -721,7 +721,7 @@ impl fmt::Debug for Registry {
 #[cfg(all(
     unix,
     not(mio_unsupported_force_poll_poll),
-    not(any(target_os = "solaris", target_os = "vita"))
+    not(any(target_os = "solaris", target_os = "vita", target_os = "irix"))
 ))]
 impl AsRawFd for Registry {
     fn as_raw_fd(&self) -> RawFd {
@@ -733,7 +733,7 @@ cfg_os_poll! {
     #[cfg(all(
         unix,
         not(mio_unsupported_force_poll_poll),
-        not(any(target_os = "solaris", target_os = "vita")),
+        not(any(target_os = "solaris", target_os = "vita", target_os = "irix")),
     ))]
     #[test]
     pub fn as_raw_fd() {
