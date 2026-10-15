$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/net/send_recv.rs.orig
+++ rustix-1.1.5/src/backend/libc/net/send_recv.rs
@@ -20,6 +20,7 @@ bitflags! {
             target_os = "espidf",
             target_os = "nto",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "horizon",
             target_os = "hurd",
             target_os = "redox",
@@ -42,13 +43,14 @@ bitflags! {
             target_os = "aix",
             target_os = "cygwin",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
             target_os = "vita",
         )))]
         const MORE = bitcast!(c::MSG_MORE);
-        #[cfg(not(any(apple, windows, target_os = "redox", target_os = "vita")))]
+        #[cfg(not(any(target_os = "irix", apple, windows, target_os = "redox", target_os = "vita")))]
         /// `MSG_NOSIGNAL`
         const NOSIGNAL = bitcast!(c::MSG_NOSIGNAL);
         /// `MSG_OOB`
@@ -76,6 +78,7 @@ bitflags! {
             target_os = "aix",
             target_os = "espidf",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "horizon",
             target_os = "nto",
             target_os = "redox",
@@ -94,6 +97,7 @@ bitflags! {
             target_os = "cygwin",
             target_os = "espidf",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "horizon",
             target_os = "hurd",
             target_os = "nto",
