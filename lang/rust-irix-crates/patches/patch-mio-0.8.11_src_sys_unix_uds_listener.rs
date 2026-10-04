$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- mio-0.8.11/src/sys/unix/uds/listener.rs.orig
+++ mio-0.8.11/src/sys/unix/uds/listener.rs
@@ -45,6 +45,7 @@ pub(crate) fn accept(listener: &net::UnixListener) -> io::Result<(UnixStream, So
 
     #[cfg(not(any(
         target_os = "aix",
+        target_os = "irix",
         target_os = "ios",
         target_os = "macos",
         target_os = "netbsd",
@@ -53,6 +54,7 @@ pub(crate) fn accept(listener: &net::UnixListener) -> io::Result<(UnixStream, So
         target_os = "watchos",
         target_os = "espidf",
         target_os = "vita",
+        target_os = "irix",
         // Android x86's seccomp profile forbids calls to `accept4(2)`
         // See https://github.com/tokio-rs/mio/issues/1445 for details
         all(target_arch = "x86", target_os = "android"),
@@ -70,6 +72,7 @@ pub(crate) fn accept(listener: &net::UnixListener) -> io::Result<(UnixStream, So
 
     #[cfg(any(
         target_os = "aix",
+        target_os = "irix",
         target_os = "ios",
         target_os = "macos",
         target_os = "netbsd",
@@ -78,6 +81,7 @@ pub(crate) fn accept(listener: &net::UnixListener) -> io::Result<(UnixStream, So
         target_os = "watchos",
         target_os = "espidf",
         target_os = "vita",
+        target_os = "irix",
         all(target_arch = "x86", target_os = "android")
     ))]
     let socket = syscall!(accept(
@@ -89,7 +93,7 @@ pub(crate) fn accept(listener: &net::UnixListener) -> io::Result<(UnixStream, So
         // Ensure the socket is closed if either of the `fcntl` calls
         // error below.
         let s = unsafe { net::UnixStream::from_raw_fd(socket) };
-        #[cfg(not(any(target_os = "espidf", target_os = "vita")))]
+        #[cfg(not(any(target_os = "espidf", target_os = "vita", target_os = "irix")))]
         syscall!(fcntl(socket, libc::F_SETFD, libc::FD_CLOEXEC))?;
 
         // See https://github.com/tokio-rs/mio/issues/1450
@@ -97,6 +101,7 @@ pub(crate) fn accept(listener: &net::UnixListener) -> io::Result<(UnixStream, So
             all(target_arch = "x86", target_os = "android"),
             target_os = "espidf",
             target_os = "vita",
+            target_os = "irix",
         ))]
         syscall!(fcntl(socket, libc::F_SETFL, libc::O_NONBLOCK))?;
 
