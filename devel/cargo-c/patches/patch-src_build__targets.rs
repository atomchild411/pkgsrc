$NetBSD$

IRIX: an ELF Unix, with shared libraries named and linked as on the BSDs and Linux (libNAME.so.N, -soname).

--- src/build_targets.rs.orig
+++ src/build_targets.rs
@@ -165,7 +165,7 @@
     ) -> Option<Self> {
         let (shared_lib, static_lib, impl_lib, debug_info, def) = match target.os.as_str() {
             "none" | "linux" | "freebsd" | "dragonfly" | "netbsd" | "android" | "haiku"
-            | "illumos" | "openbsd" | "emscripten" | "hurd" => {
+            | "illumos" | "openbsd" | "emscripten" | "hurd" | "irix" => {
                 let static_lib = targetdir.join(format!("lib{lib_name}.a"));
                 let shared_lib = targetdir.join(format!("lib{lib_name}.so"));
                 (shared_lib, static_lib, None, None, None)
