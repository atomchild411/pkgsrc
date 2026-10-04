$NetBSD$

IRIX 6.5 (mips64-sgi-irix): the poll() selector and plain accept/pipe, as on the systems without epoll, kqueue, accept4 or pipe2.

--- mio-1.2.3/src/sys/unix/uds/mod.rs.orig
+++ mio-1.2.3/src/sys/unix/uds/mod.rs
@@ -91,6 +91,7 @@ where
         target_os = "ios",
         target_os = "macos",
         target_os = "nto",
+        target_os = "irix",
         target_os = "tvos",
         target_os = "visionos",
         target_os = "watchos",
@@ -116,6 +117,7 @@ where
         target_os = "ios",
         target_os = "macos",
         target_os = "nto",
+        target_os = "irix",
         target_os = "tvos",
         target_os = "visionos",
         target_os = "watchos",
@@ -125,10 +127,10 @@ where
     ))]
     {
         syscall!(fcntl(fds[0], libc::F_SETFL, libc::O_NONBLOCK))?;
-        #[cfg(not(any(target_os = "espidf", target_os = "vita", target_os = "nto")))]
+        #[cfg(not(any(target_os = "espidf", target_os = "vita", target_os = "nto", target_os = "irix")))]
         syscall!(fcntl(fds[0], libc::F_SETFD, libc::FD_CLOEXEC))?;
         syscall!(fcntl(fds[1], libc::F_SETFL, libc::O_NONBLOCK))?;
-        #[cfg(not(any(target_os = "espidf", target_os = "vita", target_os = "nto")))]
+        #[cfg(not(any(target_os = "espidf", target_os = "vita", target_os = "nto", target_os = "irix")))]
         syscall!(fcntl(fds[1], libc::F_SETFD, libc::FD_CLOEXEC))?;
     }
 
