$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/sys/uio.rs.orig
+++ nix-0.29.0/src/sys/uio.rs
@@ -53,7 +53,7 @@
 /// or an error occurs. The file offset is not changed.
 ///
 /// See also: [`writev`](fn.writev.html) and [`pwrite`](fn.pwrite.html)
-#[cfg(not(any(target_os = "redox", target_os = "haiku", target_os = "solaris")))]
+#[cfg(not(any(target_os = "redox", target_os = "haiku", target_os = "solaris", target_os = "irix")))]
 pub fn pwritev<Fd: AsFd>(
     fd: Fd,
     iov: &[IoSlice<'_>],
@@ -82,7 +82,7 @@
 /// changed.
 ///
 /// See also: [`readv`](fn.readv.html) and [`pread`](fn.pread.html)
-#[cfg(not(any(target_os = "redox", target_os = "haiku", target_os = "solaris")))]
+#[cfg(not(any(target_os = "redox", target_os = "haiku", target_os = "solaris", target_os = "irix")))]
 // Clippy doesn't know that we need to pass iov mutably only because the
 // mutation happens after converting iov to a pointer
 #[allow(clippy::needless_pass_by_ref_mut)]
