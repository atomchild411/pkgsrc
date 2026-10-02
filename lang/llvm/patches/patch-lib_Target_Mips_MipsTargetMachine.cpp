$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Add the IRIX target: triple, ELF, EH encodings, n32 codegen
- R10000 scheduling model, CPUs r10000 to r16000, and -mtune

--- lib/Target/Mips/MipsTargetMachine.cpp.orig
+++ lib/Target/Mips/MipsTargetMachine.cpp
@@ -148,7 +148,8 @@ MipsTargetMachine::MipsTargetMachine(const Target &T, const Triple &TT,
   initAsmInfo();
 
   // Mips supports the debug entry values.
-  setSupportsDebugEntryValues(true);
+  // Except on IRIX, whose debuggers do not understand DW_OP_entry_value.
+  setSupportsDebugEntryValues(!TT.isOSIRIX());
 }
 
 MipsTargetMachine::~MipsTargetMachine() = default;
@@ -176,10 +177,13 @@ MipselTargetMachine::MipselTargetMachine(const Target &T, const Triple &TT,
 const MipsSubtarget *
 MipsTargetMachine::getSubtargetImpl(const Function &F) const {
   Attribute CPUAttr = F.getFnAttribute("target-cpu");
+  Attribute TuneAttr = F.getFnAttribute("tune-cpu");
   Attribute FSAttr = F.getFnAttribute("target-features");
 
   std::string CPU =
       CPUAttr.isValid() ? CPUAttr.getValueAsString().str() : TargetCPU;
+  std::string TuneCPU =
+      TuneAttr.isValid() ? TuneAttr.getValueAsString().str() : CPU;
   std::string FS =
       FSAttr.isValid() ? FSAttr.getValueAsString().str() : TargetFS;
   bool hasMips16Attr = F.getFnAttribute("mips16").isValid();
@@ -204,7 +208,7 @@ MipsTargetMachine::getSubtargetImpl(const Function &F) const {
   if (softFloat)
     FS += FS.empty() ? "+soft-float" : ",+soft-float";
 
-  auto &I = SubtargetMap[CPU + FS];
+  auto &I = SubtargetMap[CPU + "," + TuneCPU + "," + FS];
   if (!I) {
     // This needs to be done before we create a new subtarget since any
     // creation will depend on the TM and the code generation flags on the
@@ -212,7 +216,7 @@ MipsTargetMachine::getSubtargetImpl(const Function &F) const {
     resetTargetOptions(F);
     I = std::make_unique<MipsSubtarget>(
         TargetTriple, CPU, FS, isLittle, *this,
-        MaybeAlign(F.getParent()->getOverrideStackAlignment()));
+        MaybeAlign(F.getParent()->getOverrideStackAlignment()), TuneCPU);
   }
   return I.get();
 }
