$NetBSD$

IRIX 6.5 (mips64-sgi-irix): /dev/urandom; errno from __oserror() (as getrandom 0.2 here).

--- getrandom-0.1.16/src/use_file.rs.orig
+++ getrandom-0.1.16/src/use_file.rs
@@ -24,7 +24,7 @@
     target_os = "illumos"
 ))]
 const FILE_PATH: &str = "/dev/random\0";
-#[cfg(any(target_os = "android", target_os = "linux"))]
+#[cfg(any(target_os = "android", target_os = "linux", target_os = "irix"))]
 const FILE_PATH: &str = "/dev/urandom\0";
 
 pub fn getrandom_inner(dest: &mut [u8]) -> Result<(), Error> {
