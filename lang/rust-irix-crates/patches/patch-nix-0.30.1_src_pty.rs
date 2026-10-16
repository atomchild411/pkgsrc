$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.30.1/src/pty.rs.orig
+++ nix-0.30.1/src/pty.rs
@@ -5,12 +5,12 @@
 
 use std::ffi::CStr;
 use std::io;
-#[cfg(not(target_os = "aix"))]
+#[cfg(not(any(target_os = "aix", target_os = "irix")))]
 use std::mem;
 use std::os::unix::prelude::*;
 
 use crate::errno::Errno;
-#[cfg(not(target_os = "aix"))]
+#[cfg(not(any(target_os = "aix", target_os = "irix")))]
 use crate::sys::termios::Termios;
 #[cfg(all(feature = "process", not(target_os = "aix")))]
 use crate::unistd::Pid;
@@ -252,7 +252,7 @@
 /// the values in `winsize`. If `termios` is not `None`, the pseudoterminal's
 /// terminal settings of the slave will be set to the values in `termios`.
 #[inline]
-#[cfg(not(target_os = "aix"))]
+#[cfg(not(any(target_os = "aix", target_os = "irix")))]
 pub fn openpty<
     'a,
     'b,
@@ -347,7 +347,7 @@
 ///
 /// * [FreeBSD](https://man.freebsd.org/cgi/man.cgi?query=forkpty)
 /// * [Linux](https://man7.org/linux/man-pages/man3/forkpty.3.html)
-#[cfg(not(target_os = "aix"))]
+#[cfg(not(any(target_os = "aix", target_os = "irix")))]
 pub unsafe fn forkpty<'a, 'b, T: Into<Option<&'a Winsize>>, U: Into<Option<&'b Termios>>>(
     winsize: T,
     termios: U,
