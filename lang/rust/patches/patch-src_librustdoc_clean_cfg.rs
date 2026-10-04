$NetBSD$

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- src/librustdoc/clean/cfg.rs.orig
+++ src/librustdoc/clean/cfg.rs
@@ -502,6 +502,7 @@ fn human_readable_target_os(os: Symbol) -> Option<&'static str> {
         Hurd => "GNU/Hurd",
         IOs => "iOS",
         Illumos => "illumos",
+        Irix => "IRIX",
         L4Re => "L4Re",
         Linux => "Linux",
         LynxOs178 => "LynxOS-178",
