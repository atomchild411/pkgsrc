$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/sys/socket/mod.rs.orig
+++ nix-0.29.0/src/sys/socket/mod.rs
@@ -39,10 +39,10 @@
 pub use self::addr::{AddressFamily, UnixAddr};
 #[cfg(not(solarish))]
 pub use self::addr::{AddressFamily, UnixAddr};
-#[cfg(not(any(solarish, target_os = "haiku", target_os = "hurd", target_os = "redox")))]
+#[cfg(not(any(solarish, target_os = "haiku", target_os = "hurd", target_os = "redox", target_os = "irix")))]
 #[cfg(feature = "net")]
 pub use self::addr::{LinkAddr, SockaddrIn, SockaddrIn6};
-#[cfg(any(solarish, target_os = "haiku", target_os = "hurd", target_os = "redox"))]
+#[cfg(any(solarish, target_os = "haiku", target_os = "hurd", target_os = "redox", target_os = "irix"))]
 #[cfg(feature = "net")]
 pub use self::addr::{SockaddrIn, SockaddrIn6};
 
@@ -891,7 +891,7 @@
                 let cred: libc::cmsgcred = unsafe { ptr::read_unaligned(p as *const _) };
                 ControlMessageOwned::ScmCreds(cred.into())
             }
-            #[cfg(not(any(target_os = "aix", target_os = "haiku")))]
+            #[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "irix")))]
             (libc::SOL_SOCKET, libc::SCM_TIMESTAMP) => {
                 let tv: libc::timeval = unsafe { ptr::read_unaligned(p as *const _) };
                 ControlMessageOwned::ScmTimestamp(TimeVal::from(tv))
@@ -1169,13 +1169,15 @@
     /// The value of CMSG_LEN on this message.
     /// Safe because CMSG_LEN is always safe
     #[cfg(any(target_os = "android",
-              all(target_os = "linux", not(target_env = "musl"))))]
+              all(target_os = "linux", not(target_env = "musl")),
+              target_os = "irix"))]
     fn cmsg_len(&self) -> usize {
         unsafe{CMSG_LEN(self.len() as libc::c_uint) as usize}
     }
 
     #[cfg(not(any(target_os = "android",
-                  all(target_os = "linux", not(target_env = "musl")))))]
+                  all(target_os = "linux", not(target_env = "musl")),
+                  target_os = "irix")))]
     fn cmsg_len(&self) -> libc::c_uint {
         unsafe{CMSG_LEN(self.len() as libc::c_uint)}
     }
