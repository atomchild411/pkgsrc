$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/backend/libc/process/types.rs.orig
+++ rustix-1.1.5/src/backend/libc/process/types.rs
@@ -45,16 +45,17 @@ pub enum Resource {
         solarish,
         target_os = "cygwin",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "nto",
     )))]
     Rss = bitcast!(c::RLIMIT_RSS),
     /// `RLIMIT_NPROC`
-    #[cfg(not(any(solarish, target_os = "cygwin", target_os = "haiku")))]
+    #[cfg(not(any(solarish, target_os = "cygwin", target_os = "haiku", target_os = "irix")))]
     Nproc = bitcast!(c::RLIMIT_NPROC),
     /// `RLIMIT_NOFILE`
     Nofile = bitcast!(c::RLIMIT_NOFILE),
     /// `RLIMIT_MEMLOCK`
-    #[cfg(not(any(solarish, target_os = "aix", target_os = "cygwin", target_os = "haiku")))]
+    #[cfg(not(any(solarish, target_os = "aix", target_os = "cygwin", target_os = "haiku", target_os = "irix")))]
     Memlock = bitcast!(c::RLIMIT_MEMLOCK),
     /// `RLIMIT_AS`
     #[cfg(not(target_os = "openbsd"))]
@@ -66,6 +67,7 @@ pub enum Resource {
         target_os = "aix",
         target_os = "cygwin",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
     )))]
@@ -77,6 +79,7 @@ pub enum Resource {
         target_os = "aix",
         target_os = "cygwin",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
     )))]
@@ -88,6 +91,7 @@ pub enum Resource {
         target_os = "aix",
         target_os = "cygwin",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
     )))]
@@ -99,6 +103,7 @@ pub enum Resource {
         target_os = "aix",
         target_os = "cygwin",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
     )))]
@@ -110,6 +115,7 @@ pub enum Resource {
         target_os = "aix",
         target_os = "cygwin",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
     )))]
@@ -123,6 +129,7 @@ pub enum Resource {
         target_os = "cygwin",
         target_os = "emscripten",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
     )))]
