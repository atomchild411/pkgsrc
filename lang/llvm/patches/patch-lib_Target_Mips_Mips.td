$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- R10000 scheduling model, CPUs r10000 to r16000, and -mtune

--- lib/Target/Mips/Mips.td.orig
+++ lib/Target/Mips/Mips.td
@@ -226,6 +226,7 @@ include "MipsCombine.td"
 // Avoid forward declaration issues.
 include "MipsScheduleI6400.td"
 include "MipsScheduleP5600.td"
+include "MipsScheduleR10000.td"
 include "MipsScheduleGeneric.td"
 
 def MipsInstrInfo : InstrInfo {
@@ -235,6 +236,11 @@ def MipsInstrInfo : InstrInfo {
 // Mips processors supported.
 //===----------------------------------------------------------------------===//
 
+// Tuning for the R10000 (MipsScheduleR10000.td), which -mtune=r10000 gives
+// code for any instruction set: MIPS III code that R4400s run, say.
+def TuneR10000 : SubtargetFeature<"tune-r10000", "TuneR10000", "true",
+                                  "Schedule for the R10000 and successors">;
+
 def ImplP5600 : SubtargetFeature<"p5600", "ProcImpl",
                                  "MipsSubtarget::CPU::P5600",
                                  "The P5600 Processor", [FeatureMips32r5]>;
@@ -272,6 +278,12 @@ def : Proc<"mips64r6", [FeatureMips64r6]>;
 def : Proc<"octeon", [FeatureMips64r2, FeatureCnMips]>;
 def : Proc<"octeon+", [FeatureMips64r2, FeatureCnMips, FeatureCnMipsP]>;
 def : ProcessorModel<"p5600", MipsP5600Model, [ImplP5600]>;
+// The R12000, R14000 and R16000 are the R10000 with a larger active list,
+// better branch prediction and higher clocks.
+def : ProcessorModel<"r10000", MipsR10000Model, [FeatureMips4], [TuneR10000]>;
+def : ProcessorModel<"r12000", MipsR10000Model, [FeatureMips4], [TuneR10000]>;
+def : ProcessorModel<"r14000", MipsR10000Model, [FeatureMips4], [TuneR10000]>;
+def : ProcessorModel<"r16000", MipsR10000Model, [FeatureMips4], [TuneR10000]>;
 def : ProcessorModel<"i6400", MipsI6400Model, [ImplI6400]>;
 def : ProcessorModel<"i6500", MipsI6400Model, [ImplI6500]>;
 
