$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/sys/stat.rs.orig
+++ nix-0.29.0/src/sys/stat.rs
@@ -383,6 +383,7 @@
 ///
 /// [futimens(2)](https://pubs.opengroup.org/onlinepubs/9699919799/functions/futimens.html).
 #[inline]
+#[cfg(not(target_os = "irix"))]
 pub fn futimens(fd: RawFd, atime: &TimeSpec, mtime: &TimeSpec) -> Result<()> {
     let times: [libc::timespec; 2] = [*atime.as_ref(), *mtime.as_ref()];
     let res = unsafe { libc::futimens(fd, &times[0]) };
