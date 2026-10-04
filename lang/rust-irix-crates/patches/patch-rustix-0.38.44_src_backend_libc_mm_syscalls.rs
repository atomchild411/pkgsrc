$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as Haiku is, where it is (poll, no accept4/pipe2/ppoll, no fadvise/posix_madvise/fallocate/futimens, no TCP keepalive tuning or TIOCSCTTY), with the standard sockaddr layouts, XPG msghdr, ioctl(int, int, ...), madvise() with MADV_* and, IRIX N32 time_t being 32 bits, fix_y2038. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- rustix-0.38.44/src/backend/libc/mm/syscalls.rs.orig
+++ rustix-0.38.44/src/backend/libc/mm/syscalls.rs
@@ -28,7 +28,7 @@ pub(crate) fn madvise(addr: *mut c::c_void, len: usize, advice: Advice) -> io::R
         return unsafe { ret(c::madvise(addr, len, c::MADV_DONTNEED)) };
     }
 
-    #[cfg(not(target_os = "android"))]
+    #[cfg(not(any(target_os = "android", target_os = "irix")))]
     {
         let err = unsafe { c::posix_madvise(addr, len, advice as c::c_int) };
 
@@ -40,7 +40,7 @@ pub(crate) fn madvise(addr: *mut c::c_void, len: usize, advice: Advice) -> io::R
         }
     }
 
-    #[cfg(target_os = "android")]
+    #[cfg(any(target_os = "android", target_os = "irix"))]
     {
         if let Advice::DontNeed = advice {
             // Do nothing. Linux's `MADV_DONTNEED` isn't the same as
