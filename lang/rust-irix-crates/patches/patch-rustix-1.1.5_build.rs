$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/build.rs.orig
+++ rustix-1.1.5/build.rs
@@ -162,7 +162,8 @@ fn main() {
     }
 
     // These platforms have a 32-bit `time_t`.
-    if libc
+    if (libc && os == "irix")
+        || libc
         && (arch == "arm"
             || arch == "powerpc"
             || arch == "mips"
