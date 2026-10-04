$NetBSD$

IRIX 6.5 (mips64-sgi-irix): errno is at __oserror(). Cargo.toml: only the dependencies (and features) IRIX builds use.

--- errno-0.3.14/src/unix.rs.orig
+++ errno-0.3.14/src/unix.rs
@@ -99,6 +99,7 @@ extern "C" {
         link_name = "__errno_location"
     )]
     #[cfg_attr(target_os = "aix", link_name = "_Errno")]
+    #[cfg_attr(target_os = "irix", link_name = "__oserror")]
     #[cfg_attr(target_os = "nto", link_name = "__get_errno_ptr")]
     fn errno_location() -> *mut c_int;
 }
