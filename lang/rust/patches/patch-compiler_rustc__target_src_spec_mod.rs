$NetBSD: patch-compiler_rustc__target_src_spec_mod.rs,v 1.18 2026/04/02 19:06:34 wiz Exp $

Add entry for NetBSD/mips64el and NetBSD/m68k

IRIX: the mips64-sgi-irix target (IRIX 6.5, MIPS IV, N32) and its std.

--- compiler/rustc_target/src/spec/mod.rs.orig
+++ compiler/rustc_target/src/spec/mod.rs
@@ -1451,6 +1451,7 @@ supported_targets! {
     ("loongarch64-unknown-linux-musl", loongarch64_unknown_linux_musl),
     ("m68k-unknown-linux-gnu", m68k_unknown_linux_gnu),
     ("m68k-unknown-none-elf", m68k_unknown_none_elf),
+    ("m68k-unknown-netbsd", m68k_unknown_netbsd),
     ("csky-unknown-linux-gnuabiv2", csky_unknown_linux_gnuabiv2),
     ("csky-unknown-linux-gnuabiv2hf", csky_unknown_linux_gnuabiv2hf),
     ("mips-unknown-linux-gnu", mips_unknown_linux_gnu),
@@ -1465,6 +1466,7 @@ supported_targets! {
     ("powerpc-unknown-linux-gnuspe", powerpc_unknown_linux_gnuspe),
     ("powerpc-unknown-linux-musl", powerpc_unknown_linux_musl),
     ("powerpc-unknown-linux-muslspe", powerpc_unknown_linux_muslspe),
+    ("mips64-sgi-irix", mips64_sgi_irix),
     ("powerpc64-ibm-aix", powerpc64_ibm_aix),
     ("powerpc64-unknown-linux-gnu", powerpc64_unknown_linux_gnu),
     ("powerpc64-unknown-linux-musl", powerpc64_unknown_linux_musl),
@@ -1541,6 +1543,7 @@ supported_targets! {
     ("armv7-unknown-netbsd-eabihf", armv7_unknown_netbsd_eabihf),
     ("i586-unknown-netbsd", i586_unknown_netbsd),
     ("i686-unknown-netbsd", i686_unknown_netbsd),
+    ("mips64el-unknown-netbsd", mips64el_unknown_netbsd),
     ("mipsel-unknown-netbsd", mipsel_unknown_netbsd),
     ("powerpc-unknown-netbsd", powerpc_unknown_netbsd),
     ("riscv64gc-unknown-netbsd", riscv64gc_unknown_netbsd),
@@ -1984,6 +1987,7 @@ crate::target_spec_enum! {
         Horizon = "horizon",
         Hurd = "hurd",
         Illumos = "illumos",
+        Irix = "irix",
         IOs = "ios",
         L4Re = "l4re",
         Linux = "linux",
@@ -2065,6 +2069,7 @@ crate::target_spec_enum! {
     /// See the `cfg_abi` field of [`TargetOptions`] for more details.
     pub enum CfgAbi {
         Abi64 = "abi64",
+        AbiN32 = "abin32",
         AbiV2 = "abiv2",
         AbiV2Hf = "abiv2hf",
         Eabi = "eabi",
@@ -3527,7 +3532,7 @@ impl Target {
                     // No in-tree targets use "n32" but at least for now we let out-of-tree targets
                     // experiment with that.
                     (LlvmAbi::N64, CfgAbi::Abi64)
-                        | (LlvmAbi::N32, CfgAbi::Unspecified | CfgAbi::Other(_)),
+                        | (LlvmAbi::N32, CfgAbi::Unspecified | CfgAbi::AbiN32 | CfgAbi::Other(_)),
                     "invalid MIPS ABI name and `cfg(target_abi)` combination:\n\
                      ABI name: {}\n\
                      cfg(target_abi): {}",
