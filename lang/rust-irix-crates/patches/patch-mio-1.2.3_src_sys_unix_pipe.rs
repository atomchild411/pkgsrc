$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- mio-1.2.3/src/sys/unix/pipe.rs.orig
+++ mio-1.2.3/src/sys/unix/pipe.rs
@@ -41,6 +41,7 @@ pub(crate) fn new_raw() -> io::Result<[RawFd; 2]> {
         target_os = "watchos",
         target_os = "espidf",
         target_os = "nto",
+        target_os = "irix",
     ))]
     unsafe {
         // For platforms that don't have `pipe2(2)` we need to manually set the
