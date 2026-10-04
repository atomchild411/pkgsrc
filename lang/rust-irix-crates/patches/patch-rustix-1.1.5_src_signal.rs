$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-1.1.5/src/signal.rs.orig
+++ rustix-1.1.5/src/signal.rs
@@ -92,6 +92,7 @@ impl Signal {
         target_os = "aix",
         target_os = "cygwin",
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "nto",
@@ -149,12 +150,13 @@ impl Signal {
     pub const WINCH: Self = Self(unsafe { NonZeroI32::new_unchecked(c::SIGWINCH) });
     /// `SIGIO`, aka `SIGPOLL`
     #[doc(alias = "POLL")]
-    #[cfg(not(any(target_os = "haiku", target_os = "vita")))]
+    #[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "vita")))]
     pub const IO: Self = Self(unsafe { NonZeroI32::new_unchecked(c::SIGIO) });
     /// `SIGPWR`
     #[cfg(not(any(
         bsd,
         target_os = "haiku",
+        target_os = "irix",
         target_os = "horizon",
         target_os = "hurd",
         target_os = "vita"
@@ -313,6 +315,7 @@ impl Signal {
                 target_os = "aix",
                 target_os = "cygwin",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "horizon",
                 target_os = "hurd",
                 target_os = "nto",
@@ -354,11 +357,12 @@ impl Signal {
             c::SIGPROF => Some(Self::PROF),
             #[cfg(not(target_os = "vita"))]
             c::SIGWINCH => Some(Self::WINCH),
-            #[cfg(not(any(target_os = "haiku", target_os = "vita")))]
+            #[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "vita")))]
             c::SIGIO => Some(Self::IO),
             #[cfg(not(any(
                 bsd,
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "horizon",
                 target_os = "hurd",
                 target_os = "vita"
@@ -421,6 +425,7 @@ impl fmt::Debug for Signal {
                 target_os = "aix",
                 target_os = "cygwin",
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "horizon",
                 target_os = "hurd",
                 target_os = "nto",
@@ -462,11 +467,12 @@ impl fmt::Debug for Signal {
             Self::PROF => "Signal::PROF".fmt(f),
             #[cfg(not(target_os = "vita"))]
             Self::WINCH => "Signal::WINCH".fmt(f),
-            #[cfg(not(any(target_os = "haiku", target_os = "vita")))]
+            #[cfg(not(any(target_os = "haiku", target_os = "irix", target_os = "vita")))]
             Self::IO => "Signal::IO".fmt(f),
             #[cfg(not(any(
                 bsd,
                 target_os = "haiku",
+                target_os = "irix",
                 target_os = "horizon",
                 target_os = "hurd",
                 target_os = "vita"
