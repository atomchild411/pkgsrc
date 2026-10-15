$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/process/ioctl.rs.orig
+++ rustix-0.38.44/src/process/ioctl.rs
@@ -22,17 +22,17 @@ use backend::fd::AsFd;
 /// [FreeBSD]: https://man.freebsd.org/cgi/man.cgi?query=tty&sektion=4
 /// [NetBSD]: https://man.netbsd.org/tty.4
 /// [OpenBSD]: https://man.openbsd.org/tty.4
-#[cfg(not(any(windows, target_os = "aix", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "irix", windows, target_os = "aix", target_os = "redox", target_os = "wasi")))]
 #[inline]
 #[doc(alias = "TIOCSCTTY")]
 pub fn ioctl_tiocsctty<Fd: AsFd>(fd: Fd) -> io::Result<()> {
     unsafe { ioctl::ioctl(fd, Tiocsctty) }
 }
 
-#[cfg(not(any(windows, target_os = "aix", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "irix", windows, target_os = "aix", target_os = "redox", target_os = "wasi")))]
 struct Tiocsctty;
 
-#[cfg(not(any(windows, target_os = "aix", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "irix", windows, target_os = "aix", target_os = "redox", target_os = "wasi")))]
 unsafe impl ioctl::Ioctl for Tiocsctty {
     type Output = ();
 
