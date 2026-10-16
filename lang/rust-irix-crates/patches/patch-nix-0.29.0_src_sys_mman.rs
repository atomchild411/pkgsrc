$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/sys/mman.rs.orig
+++ nix-0.29.0/src/sys/mman.rs
@@ -38,6 +38,7 @@
     /// Additional parameters for [`mmap`].
     pub struct MapFlags: c_int {
         /// Compatibility flag. Ignored.
+        #[cfg(not(target_os = "irix"))]
         MAP_FILE;
         /// Share this mapping. Mutually exclusive with `MAP_PRIVATE`.
         MAP_SHARED;
@@ -77,7 +78,7 @@
         /// Do not reserve swap space for this mapping.
         ///
         /// This was removed in FreeBSD 11 and is unused in DragonFlyBSD.
-        #[cfg(not(any(freebsdlike, target_os = "aix", target_os = "hurd")))]
+        #[cfg(not(any(freebsdlike, target_os = "aix", target_os = "hurd", target_os = "irix")))]
         MAP_NORESERVE;
         /// Populate page tables for a mapping.
         #[cfg(linux_android)]
@@ -268,7 +269,7 @@
         #[cfg(linux_android)]
         MADV_DODUMP,
         /// Specify that the application no longer needs the pages in the given range.
-        #[cfg(not(any(target_os = "aix", target_os = "hurd")))]
+        #[cfg(not(any(target_os = "aix", target_os = "hurd", target_os = "irix")))]
         MADV_FREE,
         /// Request that the system not flush the current range to disk unless it needs to.
         #[cfg(freebsdlike)]
