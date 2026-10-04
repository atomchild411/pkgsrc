$NetBSD$

IRIX 6.5 (mips64-sgi-irix): no peer credentials for UNIX-domain sockets (an error); signed uid_t/gid_t, as on QNX. Cargo.toml: only the dependencies (and features) IRIX builds use.

--- tokio-1.53.1/src/process/mod.rs.orig
+++ tokio-1.53.1/src/process/mod.rs
@@ -684,7 +684,7 @@ impl Command {
     #[cfg(unix)]
     #[cfg_attr(docsrs, doc(cfg(unix)))]
     pub fn uid(&mut self, id: u32) -> &mut Command {
-        #[cfg(target_os = "nto")]
+        #[cfg(any(target_os = "nto", target_os = "irix"))]
         let id = id as i32;
         self.std.uid(id);
         self
@@ -695,7 +695,7 @@ impl Command {
     #[cfg(unix)]
     #[cfg_attr(docsrs, doc(cfg(unix)))]
     pub fn gid(&mut self, id: u32) -> &mut Command {
-        #[cfg(target_os = "nto")]
+        #[cfg(any(target_os = "nto", target_os = "irix"))]
         let id = id as i32;
         self.std.gid(id);
         self
