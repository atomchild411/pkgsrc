$NetBSD$

IRIX 6.5 (mips64-sgi-irix): uid_t is signed. Cargo.toml: no Windows-only dependencies, so that packages vendoring an older gix-sec 0.14 resolve offline.

--- gix-sec-0.14.2/src/identity.rs.orig
+++ gix-sec-0.14.2/src/identity.rs
@@ -42,7 +42,9 @@
             // SAFETY: there is no documented possibility for failure
             #[expect(unsafe_code)]
             let uid = unsafe { libc::geteuid() };
-            Ok(uid)
+            // uid_t is signed on some systems (IRIX)
+            #[allow(clippy::unnecessary_cast)]
+            Ok(uid as u32)
         }
         use std::str::FromStr;
 
