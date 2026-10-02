$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts
- lld: .rel.dyn starts with a null relocation

--- ELF/SyntheticSections.h.orig
+++ ELF/SyntheticSections.h
@@ -470,6 +470,8 @@ public:
   int64_t computeAddend(Ctx &) const;
 
   void computeRaw(Ctx &, SymbolTableBaseSection *symt);
+  void computeRawIRIX(Ctx &, SymbolTableBaseSection *symt);
+  Kind getKind() const { return kind; }
 
   Symbol *sym;
   const OutputSection *outputSec = nullptr;
@@ -551,8 +553,11 @@ public:
     return !relocs.empty() ||
            llvm::any_of(relocsVec, [](auto &v) { return !v.empty(); });
   }
-  size_t getSize() const override { return relocs.size() * this->entsize; }
+  size_t getSize() const override {
+    return (relocs.size() + hasNullHead()) * this->entsize;
+  }
   size_t getRelativeRelocCount() const { return numRelativeRelocs; }
+  bool hasNullHead() const;
   void mergeRels();
   void partitionRels();
   void finalizeContents() override;
@@ -657,6 +662,7 @@ public:
   void addSymbol(Symbol *sym);
   unsigned getNumSymbols() const { return symbols.size() + 1; }
   size_t getSymbolIndex(const Symbol &sym);
+  Symbol *getSectionSymbol(const OutputSection *osec);
   ArrayRef<SymbolTableEntry> getSymbols() const { return symbols; }
 
 protected:
@@ -670,6 +676,9 @@ protected:
   llvm::once_flag onceFlag;
   llvm::DenseMap<Symbol *, size_t> symbolIndexMap;
   llvm::DenseMap<OutputSection *, size_t> sectionIndexMap;
+  // IRIX: the .dynsym section symbol of each output section.
+  llvm::once_flag sectionSymbolOnce;
+  llvm::DenseMap<const OutputSection *, Symbol *> sectionSymbols;
 };
 
 template <class ELFT>
@@ -729,6 +738,7 @@ public:
   size_t getSize() const override { return size; }
 
 private:
+  unsigned numBuckets = 0;
   size_t size = 0;
 };
 
