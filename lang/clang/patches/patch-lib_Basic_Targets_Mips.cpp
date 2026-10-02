$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- clang: IRIX target info and toolchain driver
- R10000 scheduling model, CPUs r10000 to r16000, and -mtune

--- lib/Basic/Targets/Mips.cpp.orig
+++ lib/Basic/Targets/Mips.cpp
@@ -48,6 +48,7 @@ bool MipsTargetInfo::processorSupportsGPR64() const {
       .Case("octeon+", true)
       .Case("i6400", true)
       .Case("i6500", true)
+      .Cases("r10000", "r12000", "r14000", "r16000", true)
       .Default(false);
 }
 
@@ -55,7 +56,8 @@ static constexpr llvm::StringLiteral ValidCPUNames[] = {
     {"mips1"},  {"mips2"},    {"mips3"},    {"mips4"},    {"mips5"},
     {"mips32"}, {"mips32r2"}, {"mips32r3"}, {"mips32r5"}, {"mips32r6"},
     {"mips64"}, {"mips64r2"}, {"mips64r3"}, {"mips64r5"}, {"mips64r6"},
-    {"octeon"}, {"octeon+"},  {"p5600"},    {"i6400"},    {"i6500"}};
+    {"octeon"}, {"octeon+"},  {"p5600"},    {"i6400"},    {"i6500"},
+    {"r10000"}, {"r12000"},   {"r14000"},   {"r16000"}};
 
 bool MipsTargetInfo::isValidCPUName(StringRef Name) const {
   return llvm::is_contained(ValidCPUNames, Name);
@@ -95,10 +97,23 @@ void MipsTargetInfo::getTargetDefines(const LangOptions &Opts,
     Builder.defineMacro("__mips", "32");
     Builder.defineMacro("_MIPS_ISA", "_MIPS_ISA_MIPS32");
   } else {
-    Builder.defineMacro("__mips", "64");
+    if (getTriple().isOSIRIX()) {
+      // MIPSpro gives both as the ISA level (3 or 4), and SGI's headers
+      // compare them numerically.
+      StringRef Level = llvm::StringSwitch<StringRef>(CPU)
+                            .Case("mips4", "4")
+                            .Case("mips5", "5")
+                            .Cases("r10000", "r12000", "r14000", "r16000",
+                                   "4")
+                            .Default("3");
+      Builder.defineMacro("__mips", Level);
+      Builder.defineMacro("_MIPS_ISA", Level);
+    } else {
+      Builder.defineMacro("__mips", "64");
+      Builder.defineMacro("_MIPS_ISA", "_MIPS_ISA_MIPS64");
+    }
     Builder.defineMacro("__mips64");
     Builder.defineMacro("__mips64__");
-    Builder.defineMacro("_MIPS_ISA", "_MIPS_ISA_MIPS64");
   }
 
   const std::string ISARev = std::to_string(getISARev());
