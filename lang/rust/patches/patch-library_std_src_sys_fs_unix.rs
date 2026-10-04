$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/sys/fs/unix.rs.orig
+++ library/std/src/sys/fs/unix.rs
@@ -23,6 +23,7 @@ use libc::fstatat as fstatat64;
 use libc::fstatat64;
 #[cfg(any(
     target_os = "aix",
+    target_os = "irix",
     target_os = "android",
     target_os = "freebsd",
     target_os = "fuchsia",
@@ -37,6 +38,7 @@ use libc::fstatat64;
 use libc::readdir as readdir64;
 #[cfg(not(any(
     target_os = "aix",
+    target_os = "irix",
     target_os = "android",
     target_os = "freebsd",
     target_os = "fuchsia",
@@ -98,6 +100,8 @@ use crate::sys::weak::syscall;
 #[cfg(target_os = "android")]
 use crate::sys::weak::weak;
 use crate::sys::{AsInner, AsInnerMut, FromInner, IntoInner, cvt, cvt_r};
+// IRIX's canonicalize needs no null pointer.
+#[cfg_attr(target_os = "irix", allow(unused_imports))]
 use crate::{mem, ptr};
 
 pub struct File(FileDesc);
@@ -403,6 +407,7 @@ fn get_path_from_fd(fd: c_int) -> Option<PathBuf> {
 
 #[cfg(any(
     target_os = "aix",
+    target_os = "irix",
     target_os = "android",
     target_os = "freebsd",
     target_os = "fuchsia",
@@ -429,6 +434,7 @@ pub struct DirEntry {
 // `entry` field in `DirEntry` helps reduce the `cfg` boilerplate elsewhere.
 #[cfg(any(
     target_os = "aix",
+    target_os = "irix",
     target_os = "android",
     target_os = "freebsd",
     target_os = "fuchsia",
@@ -447,6 +453,7 @@ struct dirent64_min {
         target_os = "solaris",
         target_os = "illumos",
         target_os = "aix",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
     )))]
@@ -455,6 +462,7 @@ struct dirent64_min {
 
 #[cfg(not(any(
     target_os = "aix",
+    target_os = "irix",
     target_os = "android",
     target_os = "freebsd",
     target_os = "fuchsia",
@@ -847,6 +855,7 @@ impl Iterator for ReadDir {
 
     #[cfg(any(
         target_os = "aix",
+        target_os = "irix",
         target_os = "android",
         target_os = "freebsd",
         target_os = "fuchsia",
@@ -926,6 +935,7 @@ impl Iterator for ReadDir {
                         target_os = "solaris",
                         target_os = "illumos",
                         target_os = "aix",
+                        target_os = "irix",
                         target_os = "nto",
                     )))]
                     d_type: (*entry_ptr).d_type as u8,
@@ -945,6 +955,7 @@ impl Iterator for ReadDir {
 
     #[cfg(not(any(
         target_os = "aix",
+        target_os = "irix",
         target_os = "android",
         target_os = "freebsd",
         target_os = "fuchsia",
@@ -1102,6 +1113,7 @@ impl DirEntry {
         target_os = "haiku",
         target_os = "vxworks",
         target_os = "aix",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
     ))]
@@ -1115,6 +1127,7 @@ impl DirEntry {
         target_os = "haiku",
         target_os = "vxworks",
         target_os = "aix",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
     )))]
@@ -1133,6 +1146,7 @@ impl DirEntry {
 
     #[cfg(any(
         target_os = "aix",
+        target_os = "irix",
         target_os = "android",
         target_os = "cygwin",
         target_os = "emscripten",
@@ -1204,6 +1218,7 @@ impl DirEntry {
         target_os = "fuchsia",
         target_os = "redox",
         target_os = "aix",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
         target_os = "hurd",
@@ -1221,6 +1236,7 @@ impl DirEntry {
         target_os = "fuchsia",
         target_os = "redox",
         target_os = "aix",
+        target_os = "irix",
         target_os = "nto",
         target_os = "vita",
         target_os = "hurd",
@@ -1791,7 +1807,14 @@ impl File {
 
     pub fn set_times(&self, times: FileTimes) -> io::Result<()> {
         cfg_select! {
-            any(target_os = "redox", target_os = "espidf", target_os = "horizon", target_os = "nuttx") => {
+            any(
+                target_os = "redox",
+                target_os = "espidf",
+                target_os = "horizon",
+                target_os = "nuttx",
+                // IRIX cannot set a descriptor's times (no futimens, no futimes).
+                target_os = "irix"
+            ) => {
                 // Redox doesn't appear to support `UTIME_OMIT`.
                 // ESP-IDF and HorizonOS do not support `futimens` at all and the behavior for those OS is therefore
                 // the same as for Redox.
@@ -2197,6 +2220,20 @@ pub fn lstat(p: &CStr) -> io::Result<FileAttr> {
     Ok(FileAttr::from_stat64(stat))
 }
 
+#[cfg(target_os = "irix")]
+pub fn canonicalize(path: &CStr) -> io::Result<PathBuf> {
+    // IRIX's realpath() predates POSIX 2008: it fails with EINVAL unless given a buffer.
+    let mut buf = vec![0u8; libc::PATH_MAX as usize + 1];
+    let r = unsafe { libc::realpath(path.as_ptr(), buf.as_mut_ptr().cast()) };
+    if r.is_null() {
+        return Err(io::Error::last_os_error());
+    }
+    let len = unsafe { CStr::from_ptr(r).to_bytes().len() };
+    buf.truncate(len);
+    Ok(PathBuf::from(OsString::from_vec(buf)))
+}
+
+#[cfg(not(target_os = "irix"))]
 pub fn canonicalize(path: &CStr) -> io::Result<PathBuf> {
     let r = unsafe { libc::realpath(path.as_ptr(), ptr::null_mut()) };
     if r.is_null() {
@@ -2581,6 +2618,7 @@ mod remove_dir_impl {
         target_os = "haiku",
         target_os = "vxworks",
         target_os = "aix",
+        target_os = "irix",
     ))]
     fn is_dir(_ent: &DirEntry) -> Option<bool> {
         None
@@ -2592,6 +2630,7 @@ mod remove_dir_impl {
         target_os = "haiku",
         target_os = "vxworks",
         target_os = "aix",
+        target_os = "irix",
     )))]
     fn is_dir(ent: &DirEntry) -> Option<bool> {
         match ent.entry.d_type {
