$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/sys/ioctl/bsd.rs.orig
+++ nix-0.29.0/src/sys/ioctl/bsd.rs
@@ -1,10 +1,10 @@
 /// The datatype used for the ioctl number
 #[doc(hidden)]
-#[cfg(not(solarish))]
+#[cfg(not(any(solarish, target_os = "irix")))]
 pub type ioctl_num_type = ::libc::c_ulong;
 
 #[doc(hidden)]
-#[cfg(solarish)]
+#[cfg(any(solarish, target_os = "irix"))]
 pub type ioctl_num_type = ::libc::c_int;
 
 /// The datatype used for the 3rd argument
@@ -23,7 +23,12 @@
     #[doc(hidden)]
     pub const INOUT: ioctl_num_type = IN | OUT;
     #[doc(hidden)]
+    #[cfg(not(target_os = "irix"))]
     pub const IOCPARM_MASK: ioctl_num_type = 0x1fff;
+    // IRIX's <sys/ioccom.h>: parameters must be < 256 bytes.
+    #[doc(hidden)]
+    #[cfg(target_os = "irix")]
+    pub const IOCPARM_MASK: ioctl_num_type = 0xff;
 }
 
 pub use self::consts::*;
