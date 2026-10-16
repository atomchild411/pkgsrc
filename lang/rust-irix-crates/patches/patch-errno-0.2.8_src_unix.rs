$NetBSD$

IRIX 6.5 (mips64-sgi-irix): errno is at __oserror().

--- errno-0.2.8/src/unix.rs.orig
+++ errno-0.2.8/src/unix.rs
@@ -70,6 +70,7 @@ extern {
                link_name = "___errno")]
     #[cfg_attr(target_os = "linux",
                link_name = "__errno_location")]
+    #[cfg_attr(target_os = "irix", link_name = "__oserror")]
     fn errno_location() -> *mut c_int;
 
     #[cfg(feature = "std")]
