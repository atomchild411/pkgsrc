$NetBSD$

IRIX 6.5 (mips64-sgi-irix): set times through utimensat (in the toolchain's libc stand-ins), as on the BSDs and Solaris; IRIX has no futimes or lutimes for the utimes fallback.

--- filetime-0.2.29/src/unix/mod.rs.orig
+++ filetime-0.2.29/src/unix/mod.rs
@@ -25,7 +25,8 @@
                         target_os = "freebsd",
                         target_os = "netbsd",
                         target_os = "openbsd",
-                        target_os = "haiku"))] {
+                        target_os = "haiku",
+                        target_os = "irix"))] {
         mod utimensat;
         pub use self::utimensat::*;
     } else {
