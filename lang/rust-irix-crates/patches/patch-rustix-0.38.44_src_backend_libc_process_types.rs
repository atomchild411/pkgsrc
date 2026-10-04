$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/process/types.rs.orig
+++ rustix-0.38.44/src/backend/libc/process/types.rs
@@ -65,15 +65,15 @@ pub enum Resource {
     Core = bitcast!(c::RLIMIT_CORE),
     /// `RLIMIT_RSS`
     // "nto" has `RLIMIT_RSS`, but it has the same value as `RLIMIT_AS`.
-    #[cfg(not(any(apple, solarish, target_os = "nto", target_os = "haiku")))]
+    #[cfg(not(any(apple, solarish, target_os = "nto", target_os = "haiku", target_os = "irix")))]
     Rss = bitcast!(c::RLIMIT_RSS),
     /// `RLIMIT_NPROC`
-    #[cfg(not(any(solarish, target_os = "haiku")))]
+    #[cfg(not(any(target_os = "irix", solarish, target_os = "haiku")))]
     Nproc = bitcast!(c::RLIMIT_NPROC),
     /// `RLIMIT_NOFILE`
     Nofile = bitcast!(c::RLIMIT_NOFILE),
     /// `RLIMIT_MEMLOCK`
-    #[cfg(not(any(solarish, target_os = "aix", target_os = "haiku")))]
+    #[cfg(not(any(solarish, target_os = "aix", target_os = "haiku", target_os = "irix")))]
     Memlock = bitcast!(c::RLIMIT_MEMLOCK),
     /// `RLIMIT_AS`
     #[cfg(not(target_os = "openbsd"))]
@@ -84,6 +84,7 @@ pub enum Resource {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto"
     )))]
@@ -94,6 +95,7 @@ pub enum Resource {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto"
     )))]
@@ -104,6 +106,7 @@ pub enum Resource {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto"
     )))]
@@ -114,6 +117,7 @@ pub enum Resource {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto"
     )))]
@@ -124,6 +128,7 @@ pub enum Resource {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto"
     )))]
@@ -136,6 +141,7 @@ pub enum Resource {
         target_os = "android",
         target_os = "emscripten",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
     )))]
