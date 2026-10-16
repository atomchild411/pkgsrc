$NetBSD$

IRIX 6.5 (mips64-sgi-irix): a Unix with xdg-open (open: "not supported on this platform"). Cargo.toml: no Windows-only dunce (shellexecute-on-windows becomes empty), so that packages vendoring an older open 5 resolve offline.

--- open-5.4.3/src/lib.rs.orig
+++ open-5.4.3/src/lib.rs
@@ -125,7 +125,8 @@
     target_os = "illumos",
     target_os = "solaris",
     target_os = "aix",
-    target_os = "hurd"
+    target_os = "hurd",
+    target_os = "irix"
 ))]
 use unix as os;
 
@@ -145,7 +146,8 @@
     target_os = "haiku",
     target_os = "redox",
     target_os = "aix",
-    target_os = "hurd"
+    target_os = "hurd",
+    target_os = "irix"
 )))]
 compile_error!("open is not supported on this platform");
 
@@ -451,7 +453,8 @@
     target_os = "illumos",
     target_os = "solaris",
     target_os = "aix",
-    target_os = "hurd"
+    target_os = "hurd",
+    target_os = "irix"
 ))]
 mod wsl;
 
@@ -465,7 +468,8 @@
     target_os = "illumos",
     target_os = "solaris",
     target_os = "aix",
-    target_os = "hurd"
+    target_os = "hurd",
+    target_os = "irix"
 ))]
 mod unix;
 
