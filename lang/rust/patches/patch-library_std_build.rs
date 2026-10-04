$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/build.rs.orig
+++ library/std/build.rs
@@ -47,6 +47,7 @@ fn main() {
         || (target_vendor == "nintendo" && target_env == "newlib")
         || target_os == "vita"
         || target_os == "aix"
+        || target_os == "irix"
         || target_os == "nto"
         || target_os == "xous"
         || target_os == "hurd"
