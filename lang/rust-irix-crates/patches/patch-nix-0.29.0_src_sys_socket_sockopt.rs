$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it (as nix-0.31.3).

--- nix-0.29.0/src/sys/socket/sockopt.rs.orig
+++ nix-0.29.0/src/sys/socket/sockopt.rs
@@ -581,7 +581,8 @@
 #[cfg(not(any(
     target_os = "openbsd",
     target_os = "haiku",
-    target_os = "redox"
+    target_os = "redox",
+    target_os = "irix",
 )))]
 #[cfg(feature = "net")]
 sockopt_impl!(
@@ -607,7 +608,8 @@
 #[cfg(not(any(
     target_os = "openbsd",
     target_os = "haiku",
-    target_os = "redox"
+    target_os = "redox",
+    target_os = "irix",
 )))]
 #[cfg(feature = "net")]
 sockopt_impl!(
@@ -749,7 +751,7 @@
     libc::SO_TIMESTAMPING,
     super::TimestampingFlag
 );
-#[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "hurd", target_os = "redox")))]
+#[cfg(not(any(target_os = "aix", target_os = "haiku", target_os = "hurd", target_os = "redox", target_os = "irix")))]
 sockopt_impl!(
     /// Enable or disable the receiving of the `SO_TIMESTAMP` control message.
     ReceiveTimestamp,
@@ -1540,6 +1542,7 @@
 }
 
 /// Getter for a `OsString` value.
+#[cfg_attr(target_os = "irix", allow(dead_code))]
 struct GetOsString<T: AsMut<[u8]>> {
     len: socklen_t,
     val: MaybeUninit<T>,
@@ -1569,6 +1572,7 @@
 }
 
 /// Setter for a `OsString` value.
+#[cfg_attr(target_os = "irix", allow(dead_code))]
 struct SetOsString<'a> {
     val: &'a OsStr,
 }
@@ -1590,6 +1594,7 @@
 }
 
 /// Getter for a `CString` value.
+#[cfg_attr(target_os = "irix", allow(dead_code))]
 struct GetCString<T: AsMut<[u8]>> {
     len: socklen_t,
     val: MaybeUninit<T>,
