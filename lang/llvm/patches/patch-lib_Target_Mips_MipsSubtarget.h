$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- R10000 scheduling model, CPUs r10000 to r16000, and -mtune

--- lib/Target/Mips/MipsSubtarget.h.orig
+++ lib/Target/Mips/MipsSubtarget.h
@@ -69,6 +69,9 @@ class MipsSubtarget : public MipsGenSubtargetInfo {
   // Processor implementation
   CPU ProcImpl = CPU::Others;
 
+  // Tuned for the R10000 and its successors.
+  bool TuneR10000 = false;
+
   // IsLittle - The target is Little Endian
   bool IsLittle;
 
@@ -227,6 +230,9 @@ public:
   bool isPositionIndependent() const;
   /// This overrides the PostRAScheduler bit in the SchedModel for each CPU.
   bool enablePostRAScheduler() const override;
+  /// The machine scheduler, for the processors whose models it was tuned
+  /// with.
+  bool enableMachineScheduler() const override;
   void getCriticalPathRCs(RegClassVector &CriticalPathRCs) const override;
   CodeGenOptLevel getOptLevelToEnablePostRAScheduler() const override;
 
@@ -238,8 +244,11 @@ public:
 
   /// This constructor initializes the data members to match that
   /// of the specified triple.
+  /// TuneCPU, when given, is the processor to schedule and tune for, which
+  /// may differ from the one whose instruction set CPU names.
   MipsSubtarget(const Triple &TT, StringRef CPU, StringRef FS, bool little,
-                const MipsTargetMachine &TM, MaybeAlign StackAlignOverride);
+                const MipsTargetMachine &TM, MaybeAlign StackAlignOverride,
+                StringRef TuneCPU = "");
 
   ~MipsSubtarget() override;
 
@@ -251,6 +260,7 @@ public:
   bool hasMips2() const { return MipsArchVersion >= Mips2; }
   bool hasMips3() const { return MipsArchVersion >= Mips3; }
   bool hasMips4() const { return MipsArchVersion >= Mips4; }
+  bool isTunedForR10000() const { return TuneR10000; }
   bool hasMips5() const { return MipsArchVersion >= Mips5; }
   bool hasMips4_32() const { return HasMips4_32; }
   bool hasMips4_32r2() const { return HasMips4_32r2; }
@@ -369,7 +379,9 @@ public:
   // Grab relocation model
   Reloc::Model getRelocationModel() const;
 
-  MipsSubtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS,
+  MipsSubtarget &initializeSubtargetDependencies(StringRef CPU,
+                                                 StringRef TuneCPU,
+                                                 StringRef FS,
                                                  const TargetMachine &TM);
 
   /// Does the system support unaligned memory access.
