$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2.

--- mio-0.8.11/src/sys/unix/net.rs.orig
+++ mio-0.8.11/src/sys/unix/net.rs
@@ -53,13 +53,14 @@ pub(crate) fn new_socket(domain: libc::c_int, socket_type: libc::c_int) -> io::R
         target_os = "watchos",
         target_os = "espidf",
         target_os = "vita",
+        target_os = "irix",
     ))]
     {
         if let Err(err) = syscall!(fcntl(socket, libc::F_SETFL, libc::O_NONBLOCK)) {
             let _ = syscall!(close(socket));
             return Err(err);
         }
-        #[cfg(not(any(target_os = "espidf", target_os = "vita")))]
+        #[cfg(not(any(target_os = "espidf", target_os = "vita", target_os = "irix")))]
         if let Err(err) = syscall!(fcntl(socket, libc::F_SETFD, libc::FD_CLOEXEC)) {
             let _ = syscall!(close(socket));
             return Err(err);
