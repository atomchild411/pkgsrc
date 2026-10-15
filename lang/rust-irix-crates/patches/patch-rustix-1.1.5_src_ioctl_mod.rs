$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/ioctl/mod.rs.orig
+++ rustix-1.1.5/src/ioctl/mod.rs
@@ -325,7 +325,7 @@ type _Opcode = c::c_int;
 type _Opcode = c::c_ulong;
 
 // AIX, Emscripten, Fuchsia, Solaris, and WASI use a `int`.
-#[cfg(any(
+#[cfg(any(target_os = "irix", 
     solarish,
     target_os = "aix",
     target_os = "cygwin",
