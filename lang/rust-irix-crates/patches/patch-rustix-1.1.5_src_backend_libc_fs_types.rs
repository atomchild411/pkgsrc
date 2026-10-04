$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/fs/types.rs.orig
+++ rustix-1.1.5/src/backend/libc/fs/types.rs
@@ -388,6 +388,7 @@ bitflags! {
             target_os = "cygwin",
             target_os = "espidf",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "horizon",
             target_os = "wasi",
             target_os = "vita",
@@ -628,6 +629,7 @@ impl FileType {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "nto",
         target_os = "redox",
@@ -661,6 +663,7 @@ impl FileType {
     target_os = "espidf",
     target_os = "horizon",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "solaris",
     target_os = "vita",
@@ -792,6 +795,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "wasi",
         )))]
@@ -802,6 +806,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "wasi",
         )))]
@@ -815,6 +820,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "l4re",
             target_os = "linux",
@@ -827,6 +833,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "emscripten",
             target_os = "wasi",
@@ -838,6 +845,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "emscripten",
             target_os = "wasi",
@@ -849,6 +857,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "emscripten",
             target_os = "wasi",
@@ -860,6 +869,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "emscripten",
             target_os = "wasi",
@@ -903,11 +913,11 @@ bitflags! {
         const NOEXEC = c::ST_NOEXEC as u64;
 
         /// `ST_NOSUID`
-        #[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "horizon", target_os = "redox", target_os = "vita")))]
+        #[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "irix", target_os = "horizon", target_os = "redox", target_os = "vita")))]
         const NOSUID = c::ST_NOSUID as u64;
 
         /// `ST_RDONLY`
-        #[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "horizon", target_os = "redox", target_os = "vita")))]
+        #[cfg(not(any(target_os = "espidf", target_os = "haiku", target_os = "irix", target_os = "horizon", target_os = "redox", target_os = "vita")))]
         const RDONLY = c::ST_RDONLY as u64;
 
         /// `ST_RELATIME`
@@ -1068,6 +1078,7 @@ pub struct Stat {
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "netbsd",
     target_os = "nto",
@@ -1091,6 +1102,7 @@ pub type StatFs = c::statfs64;
     target_os = "cygwin",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "horizon",
     target_os = "nto",
     target_os = "redox",
