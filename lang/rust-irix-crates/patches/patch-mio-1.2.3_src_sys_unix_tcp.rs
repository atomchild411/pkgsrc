$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- mio-1.2.3/src/sys/unix/tcp.rs.orig
+++ mio-1.2.3/src/sys/unix/tcp.rs
@@ -102,6 +102,7 @@ pub(crate) fn accept(listener: &net::TcpListener) -> io::Result<(net::TcpStream,
         target_os = "vita",
         target_os = "hermit",
         target_os = "nto",
+        target_os = "irix",
         target_os = "wasi",
         target_os = "horizon",
         all(target_arch = "x86", target_os = "android"),
@@ -125,6 +126,7 @@ pub(crate) fn accept(listener: &net::TcpListener) -> io::Result<(net::TcpStream,
                 target_os = "vita",
                 target_os = "hermit",
                 target_os = "nto",
+                target_os = "irix",
                 target_os = "wasi",
             ))]
             syscall!(fcntl(s.as_raw_fd(), libc::F_SETFL, libc::O_NONBLOCK))?;
