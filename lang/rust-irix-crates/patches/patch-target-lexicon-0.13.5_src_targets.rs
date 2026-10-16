$NetBSD$

IRIX 6.5 (mips64-sgi-irix): IRIX as an operating system, so that build scripts and tools that parse the target (system-deps, maturin, pyo3-build-config) know it: Unix, SystemV calling convention, ELF, and 32-bit pointers (the N32 ABI).

--- target-lexicon-0.13.5/src/targets.rs.orig
+++ target-lexicon-0.13.5/src/targets.rs
@@ -719,6 +719,7 @@
     Horizon,
     Hurd,
     Illumos,
+    Irix,
     IOS(Option<DeploymentTarget>),
     L4re,
     Linux,
@@ -785,6 +786,7 @@
             Horizon => Cow::Borrowed("horizon"),
             Hurd => Cow::Borrowed("hurd"),
             Illumos => Cow::Borrowed("illumos"),
+            Irix => Cow::Borrowed("irix"),
             IOS(deployment_target) => darwin_version("ios", deployment_target),
             L4re => Cow::Borrowed("l4re"),
             Linux => Cow::Borrowed("linux"),
@@ -1638,6 +1640,7 @@
             "horizon" => Horizon,
             "hurd" => Hurd,
             "illumos" => Illumos,
+            "irix" => Irix,
             "l4re" => L4re,
             "linux" => Linux,
             "nebulet" => Nebulet,
