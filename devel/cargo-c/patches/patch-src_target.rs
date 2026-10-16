$NetBSD$

IRIX: an ELF Unix, with shared libraries named and linked as on the BSDs and Linux (libNAME.so.N, -soname).

--- src/target.rs.orig
+++ src/target.rs
@@ -116,6 +116,7 @@
             || os == "illumos"
             || os == "openbsd"
             || os == "hurd"
+            || os == "irix"
         {
             lines.push(if capi_config.library.versioning {
                 format!("-Wl,-soname,{unix_name}.so.{sover}")
