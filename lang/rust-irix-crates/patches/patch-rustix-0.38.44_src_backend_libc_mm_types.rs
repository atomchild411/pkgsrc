$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/mm/types.rs.orig
+++ rustix-0.38.44/src/backend/libc/mm/types.rs
@@ -85,6 +85,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -98,6 +99,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -114,6 +116,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -125,6 +128,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -136,6 +140,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -150,6 +155,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -164,6 +170,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -175,6 +182,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -184,7 +192,7 @@ bitflags! {
         #[cfg(freebsdlike)]
         const NOCORE = bitcast!(c::MAP_NOCORE);
         /// `MAP_NORESERVE`
-        #[cfg(not(any(
+        #[cfg(not(any(target_os = "irix", 
             freebsdlike,
             target_os = "aix",
             target_os = "hurd",
@@ -201,6 +209,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -212,6 +221,7 @@ bitflags! {
             solarish,
             target_os = "aix",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "redox",
         )))]
@@ -228,6 +238,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -315,35 +326,35 @@ bitflags! {
 #[non_exhaustive]
 pub enum Advice {
     /// `POSIX_MADV_NORMAL`
-    #[cfg(not(any(target_os = "android", target_os = "haiku")))]
+    #[cfg(not(any(target_os = "android", target_os = "haiku", target_os = "irix")))]
     Normal = bitcast!(c::POSIX_MADV_NORMAL),
 
     /// `POSIX_MADV_NORMAL`
-    #[cfg(any(target_os = "android", target_os = "haiku"))]
+    #[cfg(any(target_os = "android", target_os = "haiku", target_os = "irix"))]
     Normal = bitcast!(c::MADV_NORMAL),
 
     /// `POSIX_MADV_SEQUENTIAL`
-    #[cfg(not(any(target_os = "android", target_os = "haiku")))]
+    #[cfg(not(any(target_os = "android", target_os = "haiku", target_os = "irix")))]
     Sequential = bitcast!(c::POSIX_MADV_SEQUENTIAL),
 
     /// `POSIX_MADV_SEQUENTIAL`
-    #[cfg(any(target_os = "android", target_os = "haiku"))]
+    #[cfg(any(target_os = "android", target_os = "haiku", target_os = "irix"))]
     Sequential = bitcast!(c::MADV_SEQUENTIAL),
 
     /// `POSIX_MADV_RANDOM`
-    #[cfg(not(any(target_os = "android", target_os = "haiku")))]
+    #[cfg(not(any(target_os = "android", target_os = "haiku", target_os = "irix")))]
     Random = bitcast!(c::POSIX_MADV_RANDOM),
 
     /// `POSIX_MADV_RANDOM`
-    #[cfg(any(target_os = "android", target_os = "haiku"))]
+    #[cfg(any(target_os = "android", target_os = "haiku", target_os = "irix"))]
     Random = bitcast!(c::MADV_RANDOM),
 
     /// `POSIX_MADV_WILLNEED`
-    #[cfg(not(any(target_os = "android", target_os = "haiku")))]
+    #[cfg(not(any(target_os = "android", target_os = "haiku", target_os = "irix")))]
     WillNeed = bitcast!(c::POSIX_MADV_WILLNEED),
 
     /// `POSIX_MADV_WILLNEED`
-    #[cfg(any(target_os = "android", target_os = "haiku"))]
+    #[cfg(any(target_os = "android", target_os = "haiku", target_os = "irix"))]
     WillNeed = bitcast!(c::MADV_WILLNEED),
 
     /// `POSIX_MADV_DONTNEED`
@@ -351,12 +362,13 @@ pub enum Advice {
         target_os = "android",
         target_os = "emscripten",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
     )))]
     DontNeed = bitcast!(c::POSIX_MADV_DONTNEED),
 
     /// `POSIX_MADV_DONTNEED`
-    #[cfg(any(target_os = "android", target_os = "haiku"))]
+    #[cfg(any(target_os = "android", target_os = "haiku", target_os = "irix"))]
     DontNeed = bitcast!(i32::MAX - 1),
 
     /// `MADV_DONTNEED`
