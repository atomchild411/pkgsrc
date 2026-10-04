$NetBSD$

IRIX 6.5 (mips64-sgi-irix): no pthread_condattr_setclock, so condvar timeouts in CLOCK_REALTIME, as on Android. Cargo.toml: only the dependencies IRIX builds use.

--- parking_lot_core-0.9.12/src/thread_parker/unix.rs.orig
+++ parking_lot_core-0.9.12/src/thread_parker/unix.rs
@@ -127,12 +127,12 @@ impl super::ThreadParkerT for ThreadParker {
 
 impl ThreadParker {
     /// Initializes the condvar to use CLOCK_MONOTONIC instead of CLOCK_REALTIME.
-    #[cfg(any(target_vendor = "apple", target_os = "android", target_os = "espidf"))]
+    #[cfg(any(target_vendor = "apple", target_os = "android", target_os = "espidf", target_os = "irix"))]
     #[inline]
     unsafe fn init(&self) {}
 
     /// Initializes the condvar to use CLOCK_MONOTONIC instead of CLOCK_REALTIME.
-    #[cfg(not(any(target_vendor = "apple", target_os = "android", target_os = "espidf")))]
+    #[cfg(not(any(target_vendor = "apple", target_os = "android", target_os = "espidf", target_os = "irix")))]
     #[inline]
     unsafe fn init(&self) {
         let mut attr = MaybeUninit::<libc::pthread_condattr_t>::uninit();
@@ -200,7 +200,7 @@ fn timespec_now() -> libc::timespec {
 #[inline]
 fn timespec_now() -> libc::timespec {
     let mut now = MaybeUninit::<libc::timespec>::uninit();
-    let clock = if cfg!(target_os = "android") {
+    let clock = if cfg!(any(target_os = "android", target_os = "irix")) {
         // Android doesn't support pthread_condattr_setclock, so we need to
         // specify the timeout in CLOCK_REALTIME.
         libc::CLOCK_REALTIME
