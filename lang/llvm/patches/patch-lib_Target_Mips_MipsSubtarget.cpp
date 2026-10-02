$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- R10000 scheduling model, CPUs r10000 to r16000, and -mtune

--- lib/Target/Mips/MipsSubtarget.cpp.orig
+++ lib/Target/Mips/MipsSubtarget.cpp
@@ -70,8 +70,8 @@ void MipsSubtarget::anchor() {}
 
 MipsSubtarget::MipsSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
                              bool little, const MipsTargetMachine &TM,
-                             MaybeAlign StackAlignOverride)
-    : MipsGenSubtargetInfo(TT, CPU, /*TuneCPU*/ CPU, FS),
+                             MaybeAlign StackAlignOverride, StringRef TuneCPU)
+    : MipsGenSubtargetInfo(TT, CPU, TuneCPU.empty() ? CPU : TuneCPU, FS),
       MipsArchVersion(MipsDefault), IsLittle(little), IsSoftFloat(false),
       IsSingleFloat(false), IsFPXX(false), NoABICalls(false), Abs2008(false),
       IsFP64bit(false), UseOddSPReg(true), IsNaN2008bit(false),
@@ -86,7 +86,8 @@ MipsSubtarget::MipsSubtarget(const Triple &TT, StringRef CPU, StringRef FS,
       UseIndirectJumpsHazard(false), StrictAlign(false),
       StackAlignOverride(StackAlignOverride), TM(TM), TargetTriple(TT),
       InstrInfo(
-          MipsInstrInfo::create(initializeSubtargetDependencies(CPU, FS, TM))),
+          MipsInstrInfo::create(
+              initializeSubtargetDependencies(CPU, TuneCPU, FS, TM))),
       FrameLowering(MipsFrameLowering::create(*this)),
       TLInfo(MipsTargetLowering::create(TM, *this)) {
 
@@ -232,6 +233,8 @@ bool MipsSubtarget::isPositionIndependent() const {
 /// This overrides the PostRAScheduler bit in the SchedModel for any CPU.
 bool MipsSubtarget::enablePostRAScheduler() const { return true; }
 
+bool MipsSubtarget::enableMachineScheduler() const { return TuneR10000; }
+
 void MipsSubtarget::getCriticalPathRCs(RegClassVector &CriticalPathRCs) const {
   CriticalPathRCs.clear();
   CriticalPathRCs.push_back(isGP64bit() ? &Mips::GPR64RegClass
@@ -243,12 +246,13 @@ CodeGenOptLevel MipsSubtarget::getOptLevelToEnablePostRAScheduler() const {
 }
 
 MipsSubtarget &
-MipsSubtarget::initializeSubtargetDependencies(StringRef CPU, StringRef FS,
+MipsSubtarget::initializeSubtargetDependencies(StringRef CPU,
+                                               StringRef TuneCPU, StringRef FS,
                                                const TargetMachine &TM) {
   StringRef CPUName = MIPS_MC::selectMipsCPU(TM.getTargetTriple(), CPU);
 
   // Parse features string.
-  ParseSubtargetFeatures(CPUName, /*TuneCPU*/ CPUName, FS);
+  ParseSubtargetFeatures(CPUName, TuneCPU.empty() ? CPUName : TuneCPU, FS);
   // Initialize scheduling itinerary for the specified CPU.
   InstrItins = getInstrItineraryForCPU(CPUName);
 
