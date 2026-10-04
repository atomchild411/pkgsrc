$NetBSD$

IRIX 6.5 (mips64-sgi-irix): no peer credentials for UNIX-domain sockets (an error); signed uid_t/gid_t, as on QNX. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- tokio-1.53.1/src/net/unix/ucred.rs.orig
+++ tokio-1.53.1/src/net/unix/ucred.rs
@@ -78,6 +78,9 @@ pub(crate) use self::impl_noproc::get_peer_cred;
 #[cfg(target_os = "nto")]
 pub(crate) use self::impl_nto::get_peer_cred;
 
+#[cfg(target_os = "irix")]
+pub(crate) use self::impl_irix::get_peer_cred;
+
 #[cfg(any(
     target_os = "linux",
     target_os = "redox",
@@ -447,3 +450,17 @@ pub(crate) mod impl_nto {
         }
     }
 }
+
+// IRIX cannot tell who is at the other end of a UNIX-domain socket.
+#[cfg(target_os = "irix")]
+pub(crate) mod impl_irix {
+    use crate::net::unix::UnixStream;
+    use std::io;
+
+    pub(crate) fn get_peer_cred(_sock: &UnixStream) -> io::Result<super::UCred> {
+        Err(io::Error::new(
+            io::ErrorKind::Unsupported,
+            "IRIX has no peer credentials for UNIX-domain sockets",
+        ))
+    }
+}
