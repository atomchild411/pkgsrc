$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/mm/types.rs.orig
+++ rustix-1.1.5/src/backend/libc/mm/types.rs
@@ -86,6 +86,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -100,6 +101,7 @@ bitflags! {
             target_os = "aix",
             target_os = "cygwin",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -117,6 +119,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -129,6 +132,7 @@ bitflags! {
             target_os = "aix",
             target_os = "cygwin",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -141,6 +145,7 @@ bitflags! {
             target_os = "aix",
             target_os = "cygwin",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -156,6 +161,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -171,6 +177,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -183,6 +190,7 @@ bitflags! {
             target_os = "aix",
             target_os = "cygwin",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -192,7 +200,7 @@ bitflags! {
         #[cfg(freebsdlike)]
         const NOCORE = bitcast!(c::MAP_NOCORE);
         /// `MAP_NORESERVE`
-        #[cfg(not(any(
+        #[cfg(not(any(target_os = "irix", 
             freebsdlike,
             target_os = "aix",
             target_os = "hurd",
@@ -210,6 +218,7 @@ bitflags! {
             target_os = "aix",
             target_os = "cygwin",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -222,6 +231,7 @@ bitflags! {
             target_os = "aix",
             target_os = "cygwin",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "redox",
         )))]
@@ -239,6 +249,7 @@ bitflags! {
             target_os = "emscripten",
             target_os = "fuchsia",
             target_os = "haiku",
+            target_os = "irix",
             target_os = "hurd",
             target_os = "nto",
             target_os = "redox",
@@ -326,35 +337,35 @@ bitflags! {
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
@@ -362,12 +373,13 @@ pub enum Advice {
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
