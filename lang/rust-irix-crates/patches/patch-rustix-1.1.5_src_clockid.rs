$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/clockid.rs.orig
+++ rustix-1.1.5/src/clockid.rs
@@ -52,7 +52,7 @@ pub enum ClockId {
     ProcessCPUTime = c::CLOCK_PROCESS_CPUTIME_ID,
 
     /// `CLOCK_THREAD_CPUTIME_ID`
-    #[cfg(not(any(
+    #[cfg(not(any(target_os = "irix", 
         solarish,
         target_os = "horizon",
         target_os = "netbsd",
@@ -116,7 +116,7 @@ impl TryFrom<c::clockid_t> for ClockId {
                 target_os = "vita"
             )))]
             c::CLOCK_PROCESS_CPUTIME_ID => Ok(ClockId::ProcessCPUTime),
-            #[cfg(not(any(
+            #[cfg(not(any(target_os = "irix", 
                 solarish,
                 target_os = "horizon",
                 target_os = "netbsd",
