$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- mio-1.2.3/src/sys/unix/uds/listener.rs.orig
+++ mio-1.2.3/src/sys/unix/uds/listener.rs
@@ -75,6 +75,7 @@ pub(crate) fn accept(listener: &net::UnixListener) -> io::Result<(UnixStream, So
         target_os = "espidf",
         target_os = "vita",
         target_os = "nto",
+        target_os = "irix",
         target_os = "horizon",
         // Android x86's seccomp profile forbids calls to `accept4(2)`
         // See https://github.com/tokio-rs/mio/issues/1445 for details
@@ -104,6 +105,7 @@ pub(crate) fn accept(listener: &net::UnixListener) -> io::Result<(UnixStream, So
         target_os = "espidf",
         target_os = "vita",
         target_os = "nto",
+        target_os = "irix",
         target_os = "horizon",
         all(target_arch = "x86", target_os = "android")
     ))]
@@ -125,6 +127,7 @@ pub(crate) fn accept(listener: &net::UnixListener) -> io::Result<(UnixStream, So
             target_os = "espidf",
             target_os = "vita",
             target_os = "nto",
+            target_os = "irix",
         ))]
         syscall!(fcntl(socket, libc::F_SETFL, libc::O_NONBLOCK))?;
 
