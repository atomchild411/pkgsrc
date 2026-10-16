$NetBSD$

IRIX: an ELF Unix, with shared libraries named and linked as on the BSDs and Linux (libNAME.so.N, -soname).

--- src/install.rs.orig
+++ src/install.rs
@@ -105,7 +105,8 @@
             | ("illumos", _)
             | ("openbsd", _)
             | ("emscripten", _)
-            | ("hurd", _) => LibType::So,
+            | ("hurd", _)
+            | ("irix", _) => LibType::So,
             ("macos", _) | ("ios", _) | ("tvos", _) | ("visionos", _) => LibType::Dylib,
             ("windows", _) | ("cygwin", _) => LibType::Windows,
             _ => unimplemented!("The target {}-{} is not supported yet", os, env),
