$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Add the IRIX target: triple, ELF, EH encodings, n32 codegen

--- include/llvm/BinaryFormat/ELF.h.orig
+++ include/llvm/BinaryFormat/ELF.h
@@ -1216,6 +1216,7 @@ enum : unsigned {
   SHT_MIPS_REGINFO = 0x70000006,  // Register usage information
   SHT_MIPS_OPTIONS = 0x7000000d,  // General options
   SHT_MIPS_DWARF = 0x7000001e,    // DWARF debugging section.
+  SHT_MIPS_EVENTS = 0x70000021,   // IRIX .MIPS.events sections.
   SHT_MIPS_ABIFLAGS = 0x7000002a, // ABI information.
 
   SHT_MSP430_ATTRIBUTES = 0x70000003U,
