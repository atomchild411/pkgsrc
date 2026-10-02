$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Add the IRIX target: triple, ELF, EH encodings, n32 codegen

--- lib/CodeGen/TargetLoweringObjectFileImpl.cpp.orig
+++ lib/CodeGen/TargetLoweringObjectFileImpl.cpp
@@ -218,7 +218,10 @@ void TargetLoweringObjectFileELF::Initialize(MCContext &Ctx,
     // FreeBSD must be explicit about the data size and using pcrel since it's
     // assembler/linker won't do the automatic conversion that the Linux tools
     // do.
-    if (isPositionIndependent() || TgtM.getTargetTriple().isOSFreeBSD()) {
+    // IRIX takes absolute personality and LSDA pointers, like its FDEs (see
+    // MCObjectFileInfo).
+    if ((isPositionIndependent() && !TgtM.getTargetTriple().isOSIRIX()) ||
+        TgtM.getTargetTriple().isOSFreeBSD()) {
       PersonalityEncoding |= dwarf::DW_EH_PE_pcrel | dwarf::DW_EH_PE_sdata4;
       LSDAEncoding = dwarf::DW_EH_PE_pcrel | dwarf::DW_EH_PE_sdata4;
     }
