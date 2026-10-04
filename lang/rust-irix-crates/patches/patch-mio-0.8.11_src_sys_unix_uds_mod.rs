$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2.

--- mio-0.8.11/src/sys/unix/uds/mod.rs.orig
+++ mio-0.8.11/src/sys/unix/uds/mod.rs
@@ -76,12 +76,14 @@ cfg_os_poll! {
     {
         #[cfg(not(any(
             target_os = "aix",
+            target_os = "irix",
             target_os = "ios",
             target_os = "macos",
             target_os = "tvos",
             target_os = "watchos",
             target_os = "espidf",
             target_os = "vita",
+            target_os = "irix",
         )))]
         let flags = flags | libc::SOCK_NONBLOCK | libc::SOCK_CLOEXEC;
 
@@ -97,19 +99,21 @@ cfg_os_poll! {
         // there is an error, the file descriptors are closed.
         #[cfg(any(
             target_os = "aix",
+            target_os = "irix",
             target_os = "ios",
             target_os = "macos",
             target_os = "tvos",
             target_os = "watchos",
             target_os = "espidf",
             target_os = "vita",
+            target_os = "irix",
         ))]
         {
             syscall!(fcntl(fds[0], libc::F_SETFL, libc::O_NONBLOCK))?;
-            #[cfg(not(any(target_os = "espidf", target_os = "vita")))]
+            #[cfg(not(any(target_os = "espidf", target_os = "vita", target_os = "irix")))]
             syscall!(fcntl(fds[0], libc::F_SETFD, libc::FD_CLOEXEC))?;
             syscall!(fcntl(fds[1], libc::F_SETFL, libc::O_NONBLOCK))?;
-            #[cfg(not(any(target_os = "espidf", target_os = "vita")))]
+            #[cfg(not(any(target_os = "espidf", target_os = "vita", target_os = "irix")))]
             syscall!(fcntl(fds[1], libc::F_SETFD, libc::FD_CLOEXEC))?;
         }
 
