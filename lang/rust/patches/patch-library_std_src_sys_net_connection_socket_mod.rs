$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/sys/net/connection/socket/mod.rs.orig
+++ library/std/src/sys/net/connection/socket/mod.rs
@@ -47,6 +47,7 @@ cfg_select! {
         target_os = "l4re",
         target_os = "nto",
         target_os = "nuttx",
+        target_os = "irix",
         target_vendor = "apple",
     ) => {
         use c::IPV6_JOIN_GROUP as IPV6_ADD_MEMBERSHIP;
