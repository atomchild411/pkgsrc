$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2.

--- mio-0.8.11/src/sys/unix/pipe.rs.orig
+++ mio-0.8.11/src/sys/unix/pipe.rs
@@ -28,6 +28,7 @@ pub(crate) fn new_raw() -> io::Result<[RawFd; 2]> {
 
     #[cfg(any(
         target_os = "aix",
+        target_os = "irix",
         target_os = "ios",
         target_os = "macos",
         target_os = "tvos",
@@ -56,6 +57,7 @@ pub(crate) fn new_raw() -> io::Result<[RawFd; 2]> {
 
     #[cfg(not(any(
         target_os = "aix",
+        target_os = "irix",
         target_os = "android",
         target_os = "dragonfly",
         target_os = "freebsd",
@@ -71,6 +73,7 @@ pub(crate) fn new_raw() -> io::Result<[RawFd; 2]> {
         target_os = "espidf",
         target_os = "solaris",
         target_os = "vita",
+        target_os = "irix",
     )))]
     compile_error!("unsupported target for `mio::unix::pipe`");
 
@@ -560,7 +563,7 @@ impl IntoRawFd for Receiver {
     }
 }
 
-#[cfg(not(any(target_os = "illumos", target_os = "solaris", target_os = "vita")))]
+#[cfg(not(any(target_os = "illumos", target_os = "solaris", target_os = "vita", target_os = "irix")))]
 fn set_nonblocking(fd: RawFd, nonblocking: bool) -> io::Result<()> {
     let value = nonblocking as libc::c_int;
     if unsafe { libc::ioctl(fd, libc::FIONBIO, &value) } == -1 {
@@ -570,7 +573,7 @@ fn set_nonblocking(fd: RawFd, nonblocking: bool) -> io::Result<()> {
     }
 }
 
-#[cfg(any(target_os = "illumos", target_os = "solaris", target_os = "vita"))]
+#[cfg(any(target_os = "illumos", target_os = "solaris", target_os = "vita", target_os = "irix"))]
 fn set_nonblocking(fd: RawFd, nonblocking: bool) -> io::Result<()> {
     let flags = unsafe { libc::fcntl(fd, libc::F_GETFL) };
     if flags < 0 {
