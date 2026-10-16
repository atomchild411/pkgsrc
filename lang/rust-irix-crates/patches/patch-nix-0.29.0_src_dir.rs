$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/dir.rs.orig
+++ nix-0.29.0/src/dir.rs
@@ -231,7 +231,8 @@
                          target_os = "hurd",
                          solarish,
                          linux_android,
-                         apple_targets))] {
+                         apple_targets,
+                         target_os = "irix"))] {
                 self.0.d_ino as u64
             } else {
                 u64::from(self.0.d_fileno)
@@ -250,7 +251,7 @@
     /// notably, some Linux filesystems don't implement this. The caller should use `stat` or
     /// `fstat` if this returns `None`.
     pub fn file_type(&self) -> Option<Type> {
-        #[cfg(not(any(solarish, target_os = "aix", target_os = "haiku")))]
+        #[cfg(not(any(solarish, target_os = "aix", target_os = "haiku", target_os = "irix")))]
         match self.0.d_type {
             libc::DT_FIFO => Some(Type::Fifo),
             libc::DT_CHR => Some(Type::CharacterDevice),
@@ -263,7 +264,7 @@
         }
 
         // illumos, Solaris, and Haiku systems do not have the d_type member at all:
-        #[cfg(any(solarish, target_os = "aix", target_os = "haiku"))]
+        #[cfg(any(solarish, target_os = "aix", target_os = "haiku", target_os = "irix"))]
         None
     }
 }
