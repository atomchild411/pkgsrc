$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it.

--- nix-0.31.3/src/unistd.rs.orig
+++ nix-0.31.3/src/unistd.rs
@@ -1298,7 +1298,8 @@
         if #[cfg(any(freebsdlike,
                      solarish,
                      apple_targets,
-                     target_os = "aix"))] {
+                     target_os = "aix",
+                     target_os = "irix"))] {
             type sethostname_len_t = c_int;
         } else {
             type sethostname_len_t = size_t;
@@ -1961,7 +1962,8 @@
         if #[cfg(any(bsd,
                      solarish,
                      target_os = "aix",
-                     target_os = "cygwin"))] {
+                     target_os = "cygwin",
+                     target_os = "irix"))] {
             type setgroups_ngroups_t = c_int;
         } else {
             type setgroups_ngroups_t = size_t;
@@ -2350,6 +2352,7 @@
 #[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
 #[repr(i32)]
 #[non_exhaustive]
+#[cfg(not(target_os = "irix"))]
 pub enum PathconfVar {
     #[cfg(any(
         freebsdlike,
@@ -2512,6 +2515,7 @@
 /// - `Ok(None)`: the variable has no limit (for limit variables) or is
 ///     unsupported (for option variables)
 /// - `Err(x)`: an error occurred
+#[cfg(not(target_os = "irix"))]
 pub fn fpathconf<F: std::os::fd::AsFd>(fd: F, var: PathconfVar) -> Result<Option<c_long>> {
     use std::os::fd::AsRawFd;
 
@@ -2551,6 +2555,7 @@
 /// - `Ok(None)`: the variable has no limit (for limit variables) or is
 ///     unsupported (for option variables)
 /// - `Err(x)`: an error occurred
+#[cfg(not(target_os = "irix"))]
 pub fn pathconf<P: ?Sized + NixPath>(
     path: &P,
     var: PathconfVar,
@@ -3516,6 +3521,7 @@
         target_os = "hurd",
         target_os = "emscripten",
         target_os = "cygwin",
+        target_os = "irix",
     )))]
     pub class: CString,
     /// Last password change
@@ -3528,6 +3534,7 @@
         target_os = "hurd",
         target_os = "emscripten",
         target_os = "cygwin",
+        target_os = "irix",
     )))]
     pub change: libc::time_t,
     /// Expiration time of account
@@ -3540,6 +3547,7 @@
         target_os = "hurd",
         target_os = "emscripten",
         target_os = "cygwin",
+        target_os = "irix",
     )))]
     pub expire: libc::time_t,
 }
@@ -3595,6 +3603,7 @@
                     target_os = "hurd",
                     target_os = "emscripten",
                     target_os = "cygwin",
+                    target_os = "irix",
                 )))]
                 class: CString::new(CStr::from_ptr(pw.pw_class).to_bytes())
                     .unwrap(),
@@ -3607,6 +3616,7 @@
                     target_os = "hurd",
                     target_os = "emscripten",
                     target_os = "cygwin",
+                    target_os = "irix",
                 )))]
                 change: pw.pw_change,
                 #[cfg(not(any(
@@ -3618,6 +3628,7 @@
                     target_os = "hurd",
                     target_os = "emscripten",
                     target_os = "cygwin",
+                    target_os = "irix",
                 )))]
                 expire: pw.pw_expire,
             }
@@ -3661,6 +3672,7 @@
                 target_os = "hurd",
                 target_os = "emscripten",
                 target_os = "cygwin",
+                target_os = "irix",
             )))]
             pw_class: u.class.into_raw(),
             #[cfg(not(any(
@@ -3672,6 +3684,7 @@
                 target_os = "hurd",
                 target_os = "emscripten",
                 target_os = "cygwin",
+                target_os = "irix",
             )))]
             pw_change: u.change,
             #[cfg(not(any(
@@ -3683,11 +3696,12 @@
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
