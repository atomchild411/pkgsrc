$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX dlfcn.h values: RTLD_LAZY 1, RTLD_NOW 2, RTLD_GLOBAL 4, RTLD_LOCAL 0. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- libloading-0.8.9/src/os/unix/consts.rs.orig
+++ libloading-0.8.9/src/os/unix/consts.rs
@@ -58,7 +58,9 @@ mod posix {
     use self::cfg_if::cfg_if;
     use super::c_int;
     cfg_if! {
-        if #[cfg(target_os = "haiku")] {
+        if #[cfg(target_os = "irix")] {
+            pub(super) const RTLD_LAZY: c_int = 1;
+        } else if #[cfg(target_os = "haiku")] {
             pub(super) const RTLD_LAZY: c_int = 0;
         } else if #[cfg(target_os = "aix")] {
             pub(super) const RTLD_LAZY: c_int = 4;
@@ -99,7 +101,9 @@ mod posix {
     }
 
     cfg_if! {
-        if #[cfg(target_os = "haiku")] {
+        if #[cfg(target_os = "irix")] {
+            pub(super) const RTLD_NOW: c_int = 2;
+        } else if #[cfg(target_os = "haiku")] {
             pub(super) const RTLD_NOW: c_int = 1;
         } else if #[cfg(any(
             target_os = "linux",
@@ -141,7 +145,9 @@ mod posix {
     }
 
     cfg_if! {
-        if #[cfg(any(
+        if #[cfg(target_os = "irix")] {
+            pub(super) const RTLD_GLOBAL: c_int = 4;
+        } else if #[cfg(any(
             target_os = "haiku",
             all(target_os = "android",target_pointer_width = "32"),
         ))] {
@@ -192,7 +198,9 @@ mod posix {
     }
 
     cfg_if! {
-        if #[cfg(any(
+        if #[cfg(target_os = "irix")] {
+            pub(super) const RTLD_LOCAL: c_int = 0;
+        } else if #[cfg(any(
            target_os = "netbsd",
            target_os = "nto",
         ))] {
