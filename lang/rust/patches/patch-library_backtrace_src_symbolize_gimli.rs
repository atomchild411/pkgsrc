$NetBSD: patch-library_backtrace_src_symbolize_gimli.rs,v 1.9 2025/08/25 17:51:12 wiz Exp $

Add NetBSD to the family who is in the unix class.

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/backtrace/src/symbolize/gimli.rs.orig
+++ library/backtrace/src/symbolize/gimli.rs
@@ -39,10 +39,12 @@ cfg_if::cfg_if! {
         target_os = "haiku",
         target_os = "hurd",
         target_os = "linux",
+        target_os = "netbsd",
         target_os = "openbsd",
         target_os = "solaris",
         target_os = "illumos",
         target_os = "aix",
+        target_os = "irix",
         target_os = "cygwin",
     ))] {
         #[path = "gimli/mmap_unix.rs"]
@@ -247,6 +249,9 @@ cfg_if::cfg_if! {
     } else if #[cfg(target_os = "aix")] {
         mod libs_aix;
         use libs_aix::native_libraries;
+    } else if #[cfg(target_os = "irix")] {
+        mod libs_irix;
+        use libs_irix::native_libraries;
     } else {
         // Everything else should doesn't know how to load native libraries.
         fn native_libraries() -> Vec<Library> {
