$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts
- lld: place dynamic relocations in .eh_frame at their output offsets
- lld: .rel.dyn starts with a null relocation
- lld: secondary-GOT page entries name a section symbol

--- ELF/SyntheticSections.cpp.orig
+++ ELF/SyntheticSections.cpp
@@ -175,8 +175,8 @@ template <class ELFT> void MipsOptionsSection<ELFT>::writeTo(uint8_t *buf) {
 template <class ELFT>
 std::unique_ptr<MipsOptionsSection<ELFT>>
 MipsOptionsSection<ELFT>::create(Ctx &ctx) {
-  // N64 ABI only.
-  if (!ELFT::Is64Bits)
+  // N64 ABI only -- and n32 on IRIX, whose rld reads it there too.
+  if (!ELFT::Is64Bits && ctx.arg.osabi != ELFOSABI_IRIX)
     return nullptr;
 
   SmallVector<InputSectionBase *, 0> sections;
@@ -398,7 +398,11 @@ BssSection::BssSection(Ctx &ctx, StringRef name, uint64_t size,
 }
 
 EhFrameSection::EhFrameSection(Ctx &ctx)
-    : SyntheticSection(ctx, ".eh_frame", SHT_PROGBITS, SHF_ALLOC, 1) {}
+    : SyntheticSection(ctx, ".eh_frame", SHT_PROGBITS,
+                       // IRIX: absolute pointers, relocated in place by rld.
+                       ctx.arg.osabi == ELFOSABI_IRIX ? SHF_ALLOC | SHF_WRITE
+                                                      : SHF_ALLOC,
+                       1) {}
 
 // Search for an existing CIE record or create a new one.
 // CIE records from input object files are uniquified by their contents
@@ -1603,6 +1607,8 @@ DynamicSection<ELFT>::computeContents() {
       addInt(DT_MIPS_RLD_MAP_REL,
              ctx.in.mipsRldMap->getVA() - (getVA() + entries.size() * entsize));
     }
+    if (ctx.arg.osabi == ELFOSABI_IRIX && ctx.in.mipsOptions)
+      addInSec(DT_MIPS_OPTIONS, *ctx.in.mipsOptions);
   }
 
   // DT_PPC_GOT indicates to glibc Secure PLT is used. If DT_PPC_GOT is absent,
@@ -1642,6 +1648,13 @@ template <class ELFT> void DynamicSection<ELFT>::writeTo(uint8_t *buf) {
 }
 
 uint64_t DynamicReloc::getOffset() const {
+  // The relocation scanner gives .eh_frame relocations offsets in the output
+  // .eh_frame already (see OffsetGetter), which getVA would map again, as
+  // input offsets. Only IRIX puts dynamic relocations there: its .eh_frame is
+  // writable, and holds absolute pointers.
+  if (auto *eh = dyn_cast<EhInputSection>(inputSec))
+    if (InputSection *parent = eh->getParent())
+      return parent->getVA(offsetInSec);
   return inputSec->getVA(offsetInSec);
 }
 
@@ -1751,8 +1764,60 @@ void DynamicReloc::computeRaw(Ctx &ctx, SymbolTableBaseSection *symt) {
   kind = AddendOnly; // Catch errors
 }
 
+// IRIX's rld ignores a relocation whose symbol index is 0 instead of
+// relocating it by the load address, so a relocation that would name no
+// symbol names the section symbol of its target's output section instead
+// (Writer::addSectionSymbols puts those in .dynsym). The word relocated keeps
+// its full link-time value, as rld expects for symbols the object defines:
+// it adds only the distance the object moved.
+void DynamicReloc::computeRawIRIX(Ctx &ctx, SymbolTableBaseSection *symt) {
+  r_offset = getOffset();
+  r_sym = getSymIndex(symt);
+  addend = computeAddend(ctx);
+  // A page entry of a secondary (multi-)GOT names no symbol, only the output
+  // section whose page it holds.
+  const OutputSection *osec = kind == MipsMultiGotPage ? outputSec
+                              : sym && r_sym == 0      ? sym->getOutputSection()
+                                                       : nullptr;
+  if (osec) {
+    Symbol *secSym = symt->getSectionSymbol(osec);
+    if (!secSym) {
+      InternalErr(ctx, nullptr)
+          << "no section symbol for relocation against "
+          << (sym ? toStr(ctx, *sym) : osec->name.str());
+      return;
+    }
+    addend -= secSym->getVA(ctx);
+    sym = secSym;
+    kind = AgainstSymbolWithTargetVA;
+    r_sym = getSymIndex(symt);
+  }
+  // The kind stays: Writer::precomputeIRIXRelocs still needs it.
+}
+
+// The MIPS ABI starts the dynamic relocation table with a null entry, and
+// IRIX's rld skips the first entry unread: without one, the first real
+// relocation is never applied, and a shared object that rld moves keeps that
+// word at its link-time value.
+bool RelocationBaseSection::hasNullHead() const {
+  return ctx.arg.osabi == ELFOSABI_IRIX && this != ctx.in.relaPlt.get() &&
+         !relocs.empty();
+}
+
 void RelocationBaseSection::computeRels() {
   SymbolTableBaseSection *symTab = getPartition(ctx).dynSymTab.get();
+
+  if (ctx.arg.osabi == ELFOSABI_IRIX) {
+    parallelForEach(relocs, [&ctx = ctx, symTab](DynamicReloc &rel) {
+      rel.computeRawIRIX(ctx, symTab);
+    });
+    // rld needs them ordered by symbol index.
+    llvm::stable_sort(relocs, [](const DynamicReloc &a, const DynamicReloc &b) {
+      return std::tie(a.r_sym, a.r_offset) < std::tie(b.r_sym, b.r_offset);
+    });
+    return;
+  }
+
   parallelForEach(relocs, [&ctx = ctx, symTab](DynamicReloc &rel) {
     rel.computeRaw(ctx, symTab);
   });
@@ -1787,6 +1852,10 @@ RelocationSection<ELFT>::RelocationSection(Ctx &ctx, StringRef name,
 
 template <class ELFT> void RelocationSection<ELFT>::writeTo(uint8_t *buf) {
   computeRels();
+  if (hasNullHead()) {
+    memset(buf, 0, this->entsize); // R_MIPS_NONE against symbol 0
+    buf += this->entsize;
+  }
   for (const DynamicReloc &rel : relocs) {
     auto *p = reinterpret_cast<Elf_Rela *>(buf);
     p->r_offset = rel.r_offset;
@@ -2206,6 +2275,16 @@ void SymbolTableBaseSection::finalizeContents() {
     sortMipsSymbols(ctx, symbols);
   }
 
+  // IRIX's .dynsym holds local section symbols; like any symbol table's
+  // locals, they go first, and sh_info points past them. The partition is
+  // stable, so the global GOT order sortMipsSymbols set is kept.
+  if (ctx.arg.osabi == ELFOSABI_IRIX) {
+    auto firstGlobal = std::stable_partition(
+        symbols.begin(), symbols.end(),
+        [](const SymbolTableEntry &s) { return s.sym->isLocal(); });
+    getParent()->info = (firstGlobal - symbols.begin()) + 1;
+  }
+
   // Only the main partition's dynsym indexes are stored in the symbols
   // themselves. All other partitions use a lookup table.
   if (this == ctx.mainPart->dynSymTab.get()) {
@@ -2246,11 +2325,22 @@ void SymbolTableBaseSection::sortSymTabSymbols() {
 }
 
 void SymbolTableBaseSection::addSymbol(Symbol *b) {
-  // Adding a local symbol to a .dynsym is a bug.
-  assert(this->type != SHT_DYNSYM || !b->isLocal());
+  // Adding a local symbol to a .dynsym is a bug -- except IRIX's section
+  // symbols, which its rld relocates against.
+  assert(this->type != SHT_DYNSYM || !b->isLocal() ||
+         (ctx.arg.osabi == ELFOSABI_IRIX && b->type == STT_SECTION));
   symbols.push_back({b, strTabSec.addString(b->getName(), false)});
 }
 
+Symbol *SymbolTableBaseSection::getSectionSymbol(const OutputSection *osec) {
+  llvm::call_once(sectionSymbolOnce, [&] {
+    for (const SymbolTableEntry &e : symbols)
+      if (e.sym->type == STT_SECTION)
+        sectionSymbols[e.sym->getOutputSection()] = e.sym;
+  });
+  return sectionSymbols.lookup(osec);
+}
+
 size_t SymbolTableBaseSection::getSymbolIndex(const Symbol &sym) {
   if (this == ctx.mainPart->dynSymTab.get())
     return sym.dynsymIndex;
@@ -2572,8 +2662,12 @@ void HashTableSection::finalizeContents() {
   unsigned numEntries = 2;               // nbucket and nchain.
   numEntries += symTab->getNumSymbols(); // The chain entries.
 
-  // Create as many buckets as there are symbols.
-  numEntries += symTab->getNumSymbols();
+  // Create as many buckets as there are symbols -- rounded up to a power of
+  // two on IRIX, which rld and dbx expect.
+  numBuckets = symTab->getNumSymbols();
+  if (ctx.arg.osabi == ELFOSABI_IRIX)
+    numBuckets = llvm::PowerOf2Ceil(numBuckets);
+  numEntries += numBuckets;
   this->size = numEntries * 4;
 }
 
@@ -2582,17 +2676,17 @@ void HashTableSection::writeTo(uint8_t *buf) {
   unsigned numSymbols = symTab->getNumSymbols();
 
   uint32_t *p = reinterpret_cast<uint32_t *>(buf);
-  write32(ctx, p++, numSymbols); // nbucket
+  write32(ctx, p++, numBuckets); // nbucket
   write32(ctx, p++, numSymbols); // nchain
 
   uint32_t *buckets = p;
-  uint32_t *chains = p + numSymbols;
+  uint32_t *chains = p + numBuckets;
 
   for (const SymbolTableEntry &s : symTab->getSymbols()) {
     Symbol *sym = s.sym;
     StringRef name = sym->getName();
     unsigned i = sym->dynsymIndex;
-    uint32_t hash = hashSysV(name) % numSymbols;
+    uint32_t hash = hashSysV(name) % numBuckets;
     chains[i] = buckets[hash];
     write32(ctx, buckets + hash, i);
   }
