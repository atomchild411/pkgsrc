$NetBSD: patch-ELF_Config.h,v 1.10 2025/05/09 05:51:23 adam Exp $

Add dummy option for an AArch64 erratum.

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: _ftext, _fdata and _fbss, as IRIX's ld defines them

--- ELF/Config.h.orig
+++ ELF/Config.h
@@ -327,6 +327,7 @@ struct Config {
   bool enableNonContiguousRegions;
   bool executeOnly;
   bool exportDynamic;
+  bool fixCortexA53Errata835769;
   bool fixCortexA53Errata843419;
   bool fixCortexA8;
   bool formatBinary = false;
@@ -643,6 +644,12 @@ struct Ctx : CommonLinkerContext {
     Defined *end1;
     Defined *end2;
 
+    // IRIX: _ftext, _fdata and _fbss, the starts of text, data and bss that
+    // its ld defines (Boehm GC finds its data roots from _fdata).
+    Defined *ftext;
+    Defined *fdata;
+    Defined *fbss;
+
     // The _GLOBAL_OFFSET_TABLE_ symbol is defined by target convention to
     // be at some offset from the base of the .got section, usually 0 or
     // the end of the .got.
