$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/signal.rs.orig
+++ rustix-0.38.44/src/signal.rs
@@ -50,6 +50,7 @@ pub enum Signal {
         solarish,
         target_os = "aix",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "hurd",
         target_os = "nto",
         target_os = "vita",
@@ -106,10 +107,10 @@ pub enum Signal {
     Winch = c::SIGWINCH,
     /// `SIGIO`, aka `SIGPOLL`
     #[doc(alias = "Poll")]
-    #[cfg(not(any(target_os = "haiku", target_os = "vita")))]
+    #[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "vita")))]
     Io = c::SIGIO,
     /// `SIGPWR`
-    #[cfg(not(any(bsd, target_os = "haiku", target_os = "hurd", target_os = "vita")))]
+    #[cfg(not(any(bsd, target_os = "haiku", target_os = "irix", target_os = "hurd", target_os = "vita")))]
     #[doc(alias = "Pwr")]
     Power = c::SIGPWR,
     /// `SIGSYS`, aka `SIGUNUSED`
@@ -172,6 +173,7 @@ impl Signal {
                 solarish,
                 target_os = "aix",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "hurd",
                 target_os = "nto",
                 target_os = "vita",
@@ -212,9 +214,9 @@ impl Signal {
             c::SIGPROF => Some(Self::Prof),
             #[cfg(not(target_os = "vita"))]
             c::SIGWINCH => Some(Self::Winch),
-            #[cfg(not(any(target_os = "haiku", target_os = "vita")))]
+            #[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "vita")))]
             c::SIGIO => Some(Self::Io),
-            #[cfg(not(any(bsd, target_os = "haiku", target_os = "hurd", target_os = "vita")))]
+            #[cfg(not(any(bsd, target_os = "haiku", target_os = "irix", target_os = "hurd", target_os = "vita")))]
             c::SIGPWR => Some(Self::Power),
             c::SIGSYS => Some(Self::Sys),
             #[cfg(any(
