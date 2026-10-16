$NetBSD$

IRIX 6.5 (mips64-sgi-irix): nix for IRIX, as the IRIX libc crate describes it.

--- nix-0.31.3/src/sys/termios.rs.orig
+++ nix-0.31.3/src/sys/termios.rs
@@ -299,7 +299,7 @@
         B115200,
         #[cfg(solarish)]
         B153600,
-        #[cfg(not(target_os = "aix"))]
+        #[cfg(not(any(target_os = "aix", target_os = "irix")))]
         B230400,
         #[cfg(solarish)]
         B307200,
@@ -412,7 +412,8 @@
         VDISCARD,
         #[cfg(any(bsd,
                 solarish,
-                target_os = "aix"))]
+                target_os = "aix",
+                target_os = "irix"))]
         VDSUSP,
         VEOF,
         VEOL,
@@ -425,7 +426,8 @@
         #[cfg(not(target_os = "haiku"))]
         VLNEXT,
         #[cfg(not(any(all(target_os = "linux", target_arch = "sparc64"),
-                solarish, target_os = "aix", target_os = "haiku")))]
+                solarish, target_os = "aix", target_os = "haiku",
+                target_os = "irix")))]
         VMIN,
         VQUIT,
         #[cfg(not(target_os = "haiku"))]
@@ -437,10 +439,11 @@
         VSUSP,
         #[cfg(target_os = "linux")]
         VSWTC,
-        #[cfg(any(solarish, target_os = "haiku"))]
+        #[cfg(any(solarish, target_os = "haiku", target_os = "irix"))]
         VSWTCH,
         #[cfg(not(any(all(target_os = "linux", target_arch = "sparc64"),
-                solarish, target_os = "aix", target_os = "haiku")))]
+                solarish, target_os = "aix", target_os = "haiku",
+                target_os = "irix")))]
         VTIME,
         #[cfg(not(any(target_os = "aix", target_os = "haiku")))]
         VWERASE,
@@ -454,6 +457,7 @@
     solarish,
     target_os = "aix",
     target_os = "haiku",
+    target_os = "irix",
 ))]
 impl SpecialCharacterIndices {
     pub const VMIN: SpecialCharacterIndices = SpecialCharacterIndices::VEOF;
@@ -695,7 +699,7 @@
         #[cfg(bsd)]
         ALTWERASE;
         IEXTEN;
-        #[cfg(not(any(target_os = "redox", target_os = "haiku", target_os = "aix", target_os = "cygwin")))]
+        #[cfg(not(any(target_os = "redox", target_os = "haiku", target_os = "aix", target_os = "cygwin", target_os = "irix")))]
         EXTPROC;
         TOSTOP;
         #[cfg(not(target_os = "redox"))]
