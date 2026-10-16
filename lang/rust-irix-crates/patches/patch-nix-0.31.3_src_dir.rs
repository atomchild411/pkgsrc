$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it.

--- nix-0.31.3/src/dir.rs.orig
+++ nix-0.31.3/src/dir.rs
@@ -301,14 +301,15 @@
                          target_os = "cygwin",
                          solarish,
                          linux_android,
-                         apple_targets))] {
+                         apple_targets,
+                         target_os = "irix"))] {
                 let ino = de.d_ino as u64;
             } else {
                 let ino = u64::from(de.d_fileno);
             }
         }
         cfg_if! {
-            if #[cfg(not(any(solarish, target_os = "aix", target_os = "haiku")))] {
+            if #[cfg(not(any(solarish, target_os = "aix", target_os = "haiku", target_os = "irix")))] {
                 let type_ = match de.d_type {
                     libc::DT_FIFO => Some(Type::Fifo),
                     libc::DT_CHR => Some(Type::CharacterDevice),
@@ -321,7 +322,7 @@
                 };
             } else {
                 // illumos, Solaris, and Haiku systems do not have the d_type member at all:
-                #[cfg(any(solarish, target_os = "aix", target_os = "haiku"))]
+                #[cfg(any(solarish, target_os = "aix", target_os = "haiku", target_os = "irix"))]
                 let type_ = None;
             }
         }
