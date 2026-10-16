$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as an operating system, so that build scripts and tools that parse the target (system-deps, maturin, pyo3-build-config) know it: Unix, SystemV calling convention, ELF, and 32-bit pointers (the N32 ABI).

--- target-lexicon-0.12.16/src/targets.rs.orig
+++ target-lexicon-0.12.16/src/targets.rs
@@ -648,6 +648,7 @@
     Horizon,
     Hurd,
     Illumos,
+    Irix,
     Ios,
     L4re,
     Linux,
@@ -694,6 +695,7 @@
             Horizon => Cow::Borrowed("horizon"),
             Hurd => Cow::Borrowed("hurd"),
             Illumos => Cow::Borrowed("illumos"),
+            Irix => Cow::Borrowed("irix"),
             Ios => Cow::Borrowed("ios"),
             L4re => Cow::Borrowed("l4re"),
             Linux => Cow::Borrowed("linux"),
@@ -1437,6 +1439,7 @@
             "horizon" => Horizon,
             "hurd" => Hurd,
             "illumos" => Illumos,
+            "irix" => Irix,
             "ios" => Ios,
             "l4re" => L4re,
             "linux" => Linux,
