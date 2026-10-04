$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/sys/io/error/unix.rs.orig
+++ library/std/src/sys/io/error/unix.rs
@@ -30,6 +30,7 @@ unsafe extern "C" {
     #[cfg_attr(any(target_os = "freebsd", target_vendor = "apple"), link_name = "__error")]
     #[cfg_attr(target_os = "haiku", link_name = "_errnop")]
     #[cfg_attr(target_os = "aix", link_name = "_Errno")]
+    #[cfg_attr(target_os = "irix", link_name = "__oserror")]
     // SAFETY: this will always return the same pointer on a given thread.
     #[unsafe(ffi_const)]
     pub safe fn errno_location() -> *mut c_int;
