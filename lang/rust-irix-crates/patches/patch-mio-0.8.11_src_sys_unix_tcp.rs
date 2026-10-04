$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2.

--- mio-0.8.11/src/sys/unix/tcp.rs.orig
+++ mio-0.8.11/src/sys/unix/tcp.rs
@@ -84,6 +84,7 @@ pub(crate) fn accept(listener: &net::TcpListener) -> io::Result<(net::TcpStream,
     // set `CLOEXEC`.
     #[cfg(any(
         target_os = "aix",
+        target_os = "irix",
         target_os = "ios",
         target_os = "macos",
         target_os = "redox",
@@ -91,6 +92,7 @@ pub(crate) fn accept(listener: &net::TcpListener) -> io::Result<(net::TcpStream,
         target_os = "watchos",
         target_os = "espidf",
         target_os = "vita",
+        target_os = "irix",
         all(target_arch = "x86", target_os = "android"),
     ))]
     let stream = {
@@ -101,7 +103,7 @@ pub(crate) fn accept(listener: &net::TcpListener) -> io::Result<(net::TcpStream,
         ))
         .map(|socket| unsafe { net::TcpStream::from_raw_fd(socket) })
         .and_then(|s| {
-            #[cfg(not(any(target_os = "espidf", target_os = "vita")))]
+            #[cfg(not(any(target_os = "espidf", target_os = "vita", target_os = "irix")))]
             syscall!(fcntl(s.as_raw_fd(), libc::F_SETFD, libc::FD_CLOEXEC))?;
 
             // See https://github.com/tokio-rs/mio/issues/1450
@@ -109,6 +111,7 @@ pub(crate) fn accept(listener: &net::TcpListener) -> io::Result<(net::TcpStream,
                 all(target_arch = "x86", target_os = "android"),
                 target_os = "espidf",
                 target_os = "vita",
+                target_os = "irix",
             ))]
             syscall!(fcntl(s.as_raw_fd(), libc::F_SETFL, libc::O_NONBLOCK))?;
 
