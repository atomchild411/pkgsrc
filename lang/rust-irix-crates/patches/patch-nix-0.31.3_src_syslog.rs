$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it.

--- nix-0.31.3/src/syslog.rs.orig
+++ nix-0.31.3/src/syslog.rs
@@ -215,7 +215,7 @@
         /// which file descriptors are allocated.
         LOG_NDELAY;
         /// Write the message to standard error output as well to the system log.
-        #[cfg(not(any(solarish, target_os = "redox", target_os = "cygwin")))]
+        #[cfg(not(any(solarish, target_os = "redox", target_os = "cygwin", target_os = "irix")))]
         LOG_PERROR;
     }
 }
