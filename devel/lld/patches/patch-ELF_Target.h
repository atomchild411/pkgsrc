$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts

--- ELF/Target.h.orig
+++ ELF/Target.h
@@ -178,6 +178,8 @@ protected:
   // installs this is set to 65536, so the first 15 pages cannot be used.
   // Given that, the smallest value that can be used in here is 0x10000.
   uint64_t defaultImageBase = 0x10000;
+  // The base of position-independent output (shared objects).
+  uint64_t defaultPicImageBase = 0;
 };
 
 void setAArch64TargetInfo(Ctx &);
