$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/os/unix/mod.rs.orig
+++ library/std/src/os/unix/mod.rs
@@ -63,6 +63,8 @@ mod platform {
     pub use crate::os::hurd::*;
     #[cfg(target_os = "illumos")]
     pub use crate::os::illumos::*;
+    #[cfg(target_os = "irix")]
+    pub use crate::os::irix::*;
     #[cfg(target_os = "l4re")]
     pub use crate::os::l4re::*;
     #[cfg(target_os = "linux")]
