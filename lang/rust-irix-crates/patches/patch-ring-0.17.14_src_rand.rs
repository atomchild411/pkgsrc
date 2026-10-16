$NetBSD$

IRIX 6.5 (mips64-sgi-irix): system randomness through the getrandom crate (rust-irix-crates' getrandom: getentropy), as on the BSDs. Cargo.toml: no windows-sys (Windows on aarch64 only), so that packages vendoring an older ring resolve offline.

--- ring-0.17.14/src/rand.rs.orig
+++ ring-0.17.14/src/rand.rs
@@ -134,6 +134,7 @@
     target_os = "hurd",
     target_os = "horizon",
     target_os = "illumos",
+    target_os = "irix",
     target_os = "linux",
     target_os = "netbsd",
     target_os = "openbsd",
