$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/os/unix/process.rs.orig
+++ library/std/src/os/unix/process.rs
@@ -17,8 +17,9 @@ cfg_select! {
         type UserId = u16;
         type GroupId = u16;
     }
-    target_os = "nto" => {
-        // Both IDs are signed, see `sys/target_nto.h` of the QNX Neutrino SDP.
+    any(target_os = "nto", target_os = "irix") => {
+        // Both IDs are signed, see `sys/target_nto.h` of the QNX Neutrino SDP
+        // and IRIX's <sys/types.h>.
         // Only positive values should be used, see e.g.
         // https://www.qnx.com/developers/docs/7.1/#com.qnx.doc.neutrino.lib_ref/topic/s/setuid.html
         type UserId = i32;
