$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Add the IRIX target: triple, ELF, EH encodings, n32 codegen

--- lib/MC/MCObjectFileInfo.cpp.orig
+++ lib/MC/MCObjectFileInfo.cpp
@@ -346,7 +346,9 @@ void MCObjectFileInfo::initELFMCObjectFileInfo(const Triple &T, bool Large) {
     // since there is no R_MIPS_PC64 relocation (only a 32-bit version).
     // In fact DW_EH_PE_sdata4 is enough for us now, and GNU ld doesn't
     // support pcrel|sdata8 well. Let's use sdata4 for now.
-    if (PositionIndependent)
+    // IRIX's runtime linker takes absolute FDE pointers, relocated in a
+    // writable .eh_frame (see EHSectionFlags below).
+    if (PositionIndependent && !T.isOSIRIX())
       FDECFIEncoding = dwarf::DW_EH_PE_pcrel | dwarf::DW_EH_PE_sdata4;
     else
       FDECFIEncoding = Ctx->getAsmInfo()->getCodePointerSize() == 4
@@ -384,7 +386,7 @@ void MCObjectFileInfo::initELFMCObjectFileInfo(const Triple &T, bool Large) {
   // Solaris requires different flags for .eh_frame to seemingly every other
   // platform.
   unsigned EHSectionFlags = ELF::SHF_ALLOC;
-  if (T.isOSSolaris() && T.getArch() != Triple::x86_64)
+  if ((T.isOSSolaris() && T.getArch() != Triple::x86_64) || T.isOSIRIX())
     EHSectionFlags |= ELF::SHF_WRITE;
 
   // ELF
@@ -432,8 +434,11 @@ void MCObjectFileInfo::initELFMCObjectFileInfo(const Triple &T, bool Large) {
   // it contains relocatable pointers.  In PIC mode, this is probably a big
   // runtime hit for C++ apps.  Either the contents of the LSDA need to be
   // adjusted or this should be a data section.
-  LSDASection = Ctx->getELFSection(".gcc_except_table", ELF::SHT_PROGBITS,
-                                   ELF::SHF_ALLOC);
+  // On IRIX the LSDA holds absolute pointers the runtime linker relocates,
+  // so it is writable.
+  LSDASection = Ctx->getELFSection(
+      ".gcc_except_table", ELF::SHT_PROGBITS,
+      T.isOSIRIX() ? ELF::SHF_ALLOC | ELF::SHF_WRITE : ELF::SHF_ALLOC);
 
   COFFDebugSymbolsSection = nullptr;
   COFFDebugTypesSection = nullptr;
