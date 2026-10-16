$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.30.1/src/sys/mman.rs.orig
+++ nix-0.30.1/src/sys/mman.rs
@@ -38,7 +38,7 @@
     /// Additional parameters for [`mmap`].
     pub struct MapFlags: c_int {
         /// Compatibility flag. Ignored.
-        #[cfg(not(any(target_os = "solaris", target_os = "redox")))]
+        #[cfg(not(any(target_os = "solaris", target_os = "redox", target_os = "irix")))]
         MAP_FILE;
         /// Share this mapping. Mutually exclusive with `MAP_PRIVATE`.
         MAP_SHARED;
@@ -82,7 +82,7 @@
         /// Do not reserve swap space for this mapping.
         ///
         /// This was removed in FreeBSD 11 and is unused in DragonFlyBSD.
-        #[cfg(not(any(freebsdlike, target_os = "aix", target_os = "hurd", target_os = "redox")))]
+        #[cfg(not(any(freebsdlike, target_os = "aix", target_os = "hurd", target_os = "redox", target_os = "irix")))]
         MAP_NORESERVE;
         /// Populate page tables for a mapping.
         #[cfg(linux_android)]
@@ -281,7 +281,7 @@
         #[cfg(linux_android)]
         MADV_DODUMP,
         /// Specify that the application no longer needs the pages in the given range.
-        #[cfg(not(any(target_os = "aix", target_os = "hurd", target_os = "cygwin", target_os = "redox")))]
+        #[cfg(not(any(target_os = "aix", target_os = "hurd", target_os = "cygwin", target_os = "redox", target_os = "irix")))]
         MADV_FREE,
         /// Request that the system not flush the current range to disk unless it needs to.
         #[cfg(freebsdlike)]
