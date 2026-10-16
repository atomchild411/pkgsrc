$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/unistd.rs.orig
+++ nix-0.29.0/src/unistd.rs
@@ -1014,7 +1014,8 @@
         if #[cfg(any(freebsdlike,
                      solarish,
                      apple_targets,
-                     target_os = "aix"))] {
+                     target_os = "aix",
+                     target_os = "irix"))] {
             type sethostname_len_t = c_int;
         } else {
             type sethostname_len_t = size_t;
@@ -1649,7 +1650,8 @@
     cfg_if! {
         if #[cfg(any(bsd,
                      solarish,
-                     target_os = "aix"))] {
+                     target_os = "aix",
+                     target_os = "irix"))] {
             type setgroups_ngroups_t = c_int;
         } else {
             type setgroups_ngroups_t = size_t;
@@ -2027,6 +2029,7 @@
 #[derive(Clone, Copy, Debug, Eq, Hash, PartialEq)]
 #[repr(i32)]
 #[non_exhaustive]
+#[cfg(not(target_os = "irix"))]
 pub enum PathconfVar {
     #[cfg(any(
         freebsdlike,
@@ -2189,6 +2192,7 @@
 /// - `Ok(None)`: the variable has no limit (for limit variables) or is
 ///     unsupported (for option variables)
 /// - `Err(x)`: an error occurred
+#[cfg(not(target_os = "irix"))]
 pub fn fpathconf<F: AsFd>(fd: F, var: PathconfVar) -> Result<Option<c_long>> {
     let raw = unsafe {
         Errno::clear();
@@ -2226,6 +2230,7 @@
 /// - `Ok(None)`: the variable has no limit (for limit variables) or is
 ///     unsupported (for option variables)
 /// - `Err(x)`: an error occurred
+#[cfg(not(target_os = "irix"))]
 pub fn pathconf<P: ?Sized + NixPath>(
     path: &P,
     var: PathconfVar,
@@ -3190,6 +3195,7 @@
         target_os = "fuchsia",
         target_os = "haiku",
         target_os = "hurd",
+        target_os = "irix",
     )))]
     pub class: CString,
     /// Last password change
@@ -3200,6 +3206,7 @@
         target_os = "fuchsia",
         target_os = "haiku",
         target_os = "hurd",
+        target_os = "irix",
     )))]
     pub change: libc::time_t,
     /// Expiration time of account
@@ -3210,6 +3217,7 @@
         target_os = "fuchsia",
         target_os = "haiku",
         target_os = "hurd",
+        target_os = "irix",
     )))]
     pub expire: libc::time_t,
 }
@@ -3263,6 +3271,7 @@
                     target_os = "fuchsia",
                     target_os = "haiku",
                     target_os = "hurd",
+                    target_os = "irix",
                 )))]
                 class: CString::new(CStr::from_ptr(pw.pw_class).to_bytes())
                     .unwrap(),
@@ -3273,6 +3282,7 @@
                     target_os = "fuchsia",
                     target_os = "haiku",
                     target_os = "hurd",
+                    target_os = "irix",
                 )))]
                 change: pw.pw_change,
                 #[cfg(not(any(
@@ -3282,6 +3292,7 @@
                     target_os = "fuchsia",
                     target_os = "haiku",
                     target_os = "hurd",
+                    target_os = "irix",
                 )))]
                 expire: pw.pw_expire,
             }
@@ -3323,6 +3334,7 @@
                 target_os = "fuchsia",
                 target_os = "haiku",
                 target_os = "hurd",
+                target_os = "irix",
             )))]
             pw_class: u.class.into_raw(),
             #[cfg(not(any(
@@ -3332,6 +3344,7 @@
                 target_os = "fuchsia",
                 target_os = "haiku",
                 target_os = "hurd",
+                target_os = "irix",
             )))]
             pw_change: u.change,
             #[cfg(not(any(
@@ -3341,11 +3354,12 @@
                 target_os = "fuchsia",
                 target_os = "haiku",
                 target_os = "hurd",
+                target_os = "irix",
             )))]
             pw_expire: u.expire,
-            #[cfg(solarish)]
+            #[cfg(any(solarish, target_os = "irix"))]
             pw_age: CString::new("").unwrap().into_raw(),
-            #[cfg(solarish)]
+            #[cfg(any(solarish, target_os = "irix"))]
             pw_comment: CString::new("").unwrap().into_raw(),
             #[cfg(freebsdlike)]
             pw_fields: 0,
