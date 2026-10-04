$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/fs/types.rs.orig
+++ rustix-0.38.44/src/backend/libc/fs/types.rs
@@ -535,6 +535,7 @@ impl FileType {
         target_os = "aix",
         target_os = "espidf",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
         target_os = "redox",
         target_os = "vita"
@@ -567,6 +568,7 @@ impl FileType {
     target_os = "dragonfly",
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "redox",
     target_os = "vita",
 )))]
@@ -815,6 +817,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "wasi",
         )))]
@@ -825,6 +828,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "wasi",
         )))]
@@ -837,6 +841,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "l4re",
             target_os = "linux",
@@ -849,6 +854,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "emscripten",
             target_os = "wasi",
@@ -860,6 +866,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "emscripten",
             target_os = "wasi",
@@ -871,6 +878,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "emscripten",
             target_os = "wasi",
@@ -882,6 +890,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "emscripten",
             target_os = "wasi",
@@ -893,7 +902,7 @@ bitflags! {
     }
 }
 
-#[cfg(not(any(target_os = "haiku", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "redox", target_os = "wasi")))]
 bitflags! {
     /// `ST_*` constants for use with [`StatVfs`].
     #[repr(transparent)]
@@ -1055,6 +1064,7 @@ pub struct Stat {
     solarish,
     target_os = "espidf",
     target_os = "haiku",
+    target_os = "irix",
     target_os = "netbsd",
     target_os = "nto",
     target_os = "redox",
@@ -1075,7 +1085,7 @@ pub type StatFs = c::statfs64;
 ///
 /// [`statvfs`]: crate::fs::statvfs
 /// [`fstatvfs`]: crate::fs::fstatvfs
-#[cfg(not(any(target_os = "haiku", target_os = "redox", target_os = "wasi")))]
+#[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "redox", target_os = "wasi")))]
 #[allow(missing_docs)]
 pub struct StatVfs {
     pub f_bsize: u64,
