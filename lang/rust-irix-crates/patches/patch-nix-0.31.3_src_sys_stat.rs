$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it.

--- nix-0.31.3/src/sys/stat.rs.orig
+++ nix-0.31.3/src/sys/stat.rs
@@ -391,6 +391,7 @@
 ///
 /// [futimens(2)](https://pubs.opengroup.org/onlinepubs/9699919799/functions/futimens.html).
 #[inline]
+#[cfg(not(target_os = "irix"))]
 pub fn futimens<Fd: std::os::fd::AsFd>(
     fd: Fd,
     atime: &TimeSpec,
