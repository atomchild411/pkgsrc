$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/termios/mod.rs.orig
+++ rustix-0.38.44/src/termios/mod.rs
@@ -8,7 +8,7 @@
 //! [`Termios::set_input_speed`], and it will simply fail if the speed is not
 //! supported by the platform.
 
-#[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "wasi")))]
+#[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "irix", target_os = "wasi")))]
 mod ioctl;
 #[cfg(not(target_os = "wasi"))]
 mod tc;
@@ -17,7 +17,7 @@ mod tty;
 #[cfg(not(any(target_os = "espidf", target_os = "wasi")))]
 mod types;
 
-#[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "wasi")))]
+#[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "irix", target_os = "wasi")))]
 pub use ioctl::*;
 #[cfg(not(target_os = "wasi"))]
 pub use tc::*;
