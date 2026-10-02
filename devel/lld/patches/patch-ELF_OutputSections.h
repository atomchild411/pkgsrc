$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts

--- ELF/OutputSections.h.orig
+++ ELF/OutputSections.h
@@ -119,6 +119,8 @@ public:
   void writeTo(Ctx &, uint8_t *buf, llvm::parallel::TaskGroup &tg);
   // Check that the addends for dynamic relocations were written correctly.
   void checkDynRelAddends(Ctx &);
+  // IRIX: write link-time values for relocations against defined symbols.
+  void precomputeIRIXRelocs(Ctx &);
   template <class ELFT> void maybeCompress(Ctx &);
 
   void sort(llvm::function_ref<int(InputSectionBase *s)> order);
