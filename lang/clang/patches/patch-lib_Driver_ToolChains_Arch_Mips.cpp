$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- clang: IRIX target info and toolchain driver
- R10000 scheduling model, CPUs r10000 to r16000, and -mtune

--- lib/Driver/ToolChains/Arch/Mips.cpp.orig
+++ lib/Driver/ToolChains/Arch/Mips.cpp
@@ -63,6 +63,15 @@ void mips::getMipsCPUAndABI(const ArgList &Args, const llvm::Triple &Triple,
                   .Default(ABIName);
   }
 
+  // IRIX: n32 unless told otherwise; MIPS III for n32 (so R4400s run it) and
+  // MIPS IV for n64, as MIPSpro does.
+  if (Triple.isOSIRIX()) {
+    if (ABIName.empty())
+      ABIName = "n32";
+    if (CPUName.empty())
+      CPUName = ABIName == "n64" ? "mips4" : "mips3";
+  }
+
   // Setup default CPU and ABI names.
   if (CPUName.empty() && ABIName.empty()) {
     switch (Triple.getArch()) {
@@ -91,6 +100,7 @@ void mips::getMipsCPUAndABI(const ArgList &Args, const llvm::Triple &Triple,
                   .Case("mips3", "n64")
                   .Case("mips4", "n64")
                   .Case("mips5", "n64")
+                  .Cases("r10000", "r12000", "r14000", "r16000", "n64")
                   .Case("mips32", "o32")
                   .Case("mips32r2", "o32")
                   .Case("mips32r3", "o32")
@@ -424,6 +434,7 @@ mips::IEEE754Standard mips::getIEEE754Standard(StringRef &CPU) {
       .Case("mips3", Legacy)
       .Case("mips4", Legacy)
       .Case("mips5", Legacy)
+      .Cases("r10000", "r12000", "r14000", "r16000", Legacy)
       .Case("mips32", Legacy)
       .Case("mips32r2", Legacy | Std2008)
       .Case("mips32r3", Legacy | Std2008)
@@ -481,6 +492,7 @@ bool mips::isFPXXDefault(const llvm::Triple &Triple, StringRef CPUName,
 
   return llvm::StringSwitch<bool>(CPUName)
       .Cases("mips2", "mips3", "mips4", "mips5", true)
+      .Cases("r10000", "r12000", "r14000", "r16000", true)
       .Cases("mips32", "mips32r2", "mips32r3", "mips32r5", true)
       .Cases("mips64", "mips64r2", "mips64r3", "mips64r5", true)
       .Default(false);
