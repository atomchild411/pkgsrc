$NetBSD$

IRIX 6.5 (N32): the mips64-sgi-irix target's module, as IRIX looks to the
IRIX toolchain (clang with its IRIX header wrappers and builtins).

--- src/unix/mod.rs.orig
+++ src/unix/mod.rs
@@ -29,7 +29,7 @@ cfg_if! {
     ))] {
         pub type uid_t = c_ushort;
         pub type gid_t = c_ushort;
-    } else if #[cfg(any(target_os = "nto", target_os = "qnx"))] {
+    } else if #[cfg(any(target_os = "nto", target_os = "qnx", target_os = "irix"))] {
         pub type uid_t = i32;
         pub type gid_t = i32;
     } else {
@@ -601,6 +601,11 @@ cfg_if! {
         #[link(name = "bsd")]
         #[link(name = "pthread")]
         extern "C" {}
+    } else if #[cfg(target_os = "irix")] {
+        #[link(name = "pthread")]
+        #[link(name = "m")]
+        #[link(name = "c")]
+        extern "C" {}
     } else {
         #[link(name = "c")]
         #[link(name = "m")]
@@ -839,6 +844,7 @@ extern "C" {
     )]
     #[cfg_attr(target_os = "espidf", link_name = "lwip_getpeername")]
     #[cfg_attr(target_os = "aix", link_name = "ngetpeername")]
+    #[cfg_attr(target_os = "irix", link_name = "__irix_getpeername")]
     pub fn getpeername(socket: c_int, address: *mut sockaddr, address_len: *mut socklen_t)
         -> c_int;
     #[cfg(not(all(target_arch = "powerpc", target_vendor = "nintendo")))]
@@ -848,6 +854,7 @@ extern "C" {
     )]
     #[cfg_attr(target_os = "espidf", link_name = "lwip_getsockname")]
     #[cfg_attr(target_os = "aix", link_name = "ngetsockname")]
+    #[cfg_attr(target_os = "irix", link_name = "__irix_getsockname")]
     pub fn getsockname(socket: c_int, address: *mut sockaddr, address_len: *mut socklen_t)
         -> c_int;
     #[cfg_attr(target_os = "espidf", link_name = "lwip_setsockopt")]
@@ -954,6 +961,7 @@ extern "C" {
         link_name = "open$UNIX2003"
     )]
     #[cfg_attr(gnu_file_offset_bits64, link_name = "open64")]
+    #[cfg_attr(target_os = "irix", link_name = "__irix_open")]
     pub fn open(path: *const c_char, oflag: c_int, ...) -> c_int;
     #[cfg_attr(
         all(target_os = "macos", target_arch = "x86"),
@@ -970,6 +978,7 @@ extern "C" {
         all(not(gnu_time_bits64), gnu_file_offset_bits64),
         link_name = "__fcntl_time64"
     )]
+    #[cfg_attr(target_os = "irix", link_name = "__irix_fcntl")]
     pub fn fcntl(fd: c_int, cmd: c_int, ...) -> c_int;
 
     #[cfg_attr(
@@ -1225,6 +1234,7 @@ extern "C" {
         link_name = "mmap$UNIX2003"
     )]
     #[cfg_attr(gnu_file_offset_bits64, link_name = "mmap64")]
+    #[cfg_attr(target_os = "irix", link_name = "__irix_mmap")]
     pub fn mmap(
         addr: *mut c_void,
         len: size_t,
@@ -1445,6 +1455,7 @@ extern "C" {
     pub fn dlopen(filename: *const c_char, flag: c_int) -> *mut c_void;
     pub fn dlerror() -> *mut c_char;
     #[cfg_attr(musl_redir_time64, link_name = "__dlsym_time64")]
+    #[cfg_attr(target_os = "irix", link_name = "__irix_dlsym")]
     pub fn dlsym(handle: *mut c_void, symbol: *const c_char) -> *mut c_void;
     pub fn dlclose(handle: *mut c_void) -> c_int;
 
@@ -1632,6 +1643,7 @@ extern "C" {
     pub fn sigpending(set: *mut sigset_t) -> c_int;
 
     #[cfg_attr(target_os = "solaris", link_name = "__sysconf_xpg7")]
+    #[cfg_attr(target_os = "irix", link_name = "__irix_sysconf")]
     pub fn sysconf(name: c_int) -> c_long;
 
     pub fn mkfifo(path: *const c_char, mode: mode_t) -> c_int;
@@ -2508,6 +2520,9 @@ cfg_if! {
     } else if #[cfg(target_os = "aix")] {
         mod aix;
         pub use self::aix::*;
+    } else if #[cfg(target_os = "irix")] {
+        mod irix;
+        pub use self::irix::*;
     } else if #[cfg(target_os = "hurd")] {
         mod hurd;
         pub use self::hurd::*;
