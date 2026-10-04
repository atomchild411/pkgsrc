$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- library/std/src/sys/paths/unix.rs.orig
+++ library/std/src/sys/paths/unix.rs
@@ -107,7 +107,7 @@ impl fmt::Display for JoinPathsError {
 
 impl crate::error::Error for JoinPathsError {}
 
-#[cfg(target_os = "aix")]
+#[cfg(any(target_os = "aix", target_os = "irix"))]
 pub fn current_exe() -> io::Result<PathBuf> {
     #[cfg(test)]
     use realstd::env;
