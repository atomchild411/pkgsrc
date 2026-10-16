$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.30.1/src/unistd.rs.orig
+++ nix-0.30.1/src/unistd.rs
@@ -1291,7 +1291,8 @@
         if #[cfg(any(freebsdlike,
                      solarish,
                      apple_targets,
-                     target_os = "aix"))] {
+                     target_os = "aix",
+                     target_os = "irix"))] {
             type sethostname_len_t = c_int;
         } else {
             type sethostname_len_t = size_t;
@@ -1946,7 +1947,8 @@
         if #[cfg(any(bsd,
                      solarish,
                      target_os = "aix",
-                     target_os = "cygwin"))] {
+                     target_os = "cygwin",
+                     target_os = "irix"))] {
             type setgroups_ngroups_t = c_int;
         } else {
             type setgroups_ngroups_t = size_t;
@@ -2335,6 +2337,7 @@
 #[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
 #[repr(i32)]
 #[non_exhaustive]
+#[cfg(not(target_os = "irix"))]
 pub enum PathconfVar {
     #[cfg(any(
         freebsdlike,
@@ -2497,6 +2500,7 @@
 /// - `Ok(None)`: the variable has no limit (for limit variables) or is
 ///     unsupported (for option variables)
 /// - `Err(x)`: an error occurred
+#[cfg(not(target_os = "irix"))]
 pub fn fpathconf<F: std::os::fd::AsFd>(fd: F, var: PathconfVar) -> Result<Option<c_long>> {
     use std::os::fd::AsRawFd;
 
@@ -2536,6 +2540,7 @@
 /// - `Ok(None)`: the variable has no limit (for limit variables) or is
 ///     unsupported (for option variables)
 /// - `Err(x)`: an error occurred
+#[cfg(not(target_os = "irix"))]
 pub fn pathconf<P: ?Sized + NixPath>(
     path: &P,
     var: PathconfVar,
@@ -3501,6 +3506,7 @@
         target_os = "hurd",
         target_os = "emscripten",
         target_os = "cygwin",
+        target_os = "irix",
     )))]
     pub class: CString,
     /// Last password change
@@ -3513,6 +3519,7 @@
         target_os = "hurd",
         target_os = "emscripten",
         target_os = "cygwin",
+        target_os = "irix",
     )))]
     pub change: libc::time_t,
     /// Expiration time of account
@@ -3525,6 +3532,7 @@
         target_os = "hurd",
         target_os = "emscripten",
         target_os = "cygwin",
+        target_os = "irix",
     )))]
     pub expire: libc::time_t,
 }
@@ -3580,6 +3588,7 @@
                     target_os = "hurd",
                     target_os = "emscripten",
                     target_os = "cygwin",
+                    target_os = "irix",
                 )))]
                 class: CString::new(CStr::from_ptr(pw.pw_class).to_bytes())
                     .unwrap(),
@@ -3592,6 +3601,7 @@
                     target_os = "hurd",
                     target_os = "emscripten",
                     target_os = "cygwin",
+                    target_os = "irix",
                 )))]
                 change: pw.pw_change,
                 #[cfg(not(any(
@@ -3603,6 +3613,7 @@
                     target_os = "hurd",
                     target_os = "emscripten",
                     target_os = "cygwin",
+                    target_os = "irix",
                 )))]
                 expire: pw.pw_expire,
             }
@@ -3646,6 +3657,7 @@
                 target_os = "hurd",
                 target_os = "emscripten",
                 target_os = "cygwin",
+                target_os = "irix",
             )))]
             pw_class: u.class.into_raw(),
             #[cfg(not(any(
@@ -3657,6 +3669,7 @@
                 target_os = "hurd",
                 target_os = "emscripten",
                 target_os = "cygwin",
+                target_os = "irix",
             )))]
             pw_change: u.change,
             #[cfg(not(any(
@@ -3668,11 +3681,12 @@
                 target_os = "hurd",
                 target_os = "emscripten",
                 target_os = "cygwin",
+                target_os = "irix",
             )))]
             pw_expire: u.expire,
-            #[cfg(solarish)]
+            #[cfg(any(solarish, target_os = "irix"))]
             pw_age: CString::new("").unwrap().into_raw(),
-            #[cfg(any(solarish, target_os = "cygwin"))]
+            #[cfg(any(solarish, target_os = "cygwin", target_os = "irix"))]
             pw_comment: CString::new("").unwrap().into_raw(),
             #[cfg(freebsdlike)]
             pw_fields: 0,
