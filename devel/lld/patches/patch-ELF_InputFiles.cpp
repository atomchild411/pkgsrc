$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts
- lld: link-time optimization
- lld: read SGI's non-conforming relocatable objects
- lld: drop the debug information of MIPSpro objects

--- ELF/InputFiles.cpp.orig
+++ ELF/InputFiles.cpp
@@ -1611,8 +1611,12 @@ template <class ELFT> void SharedFile::parse() {
     // symbol, that's a violation of the spec.
     StringRef name = CHECK2(sym.getName(stringTable), this);
     if (sym.getBinding() == STB_LOCAL) {
-      Err(ctx) << this << ": invalid local symbol '" << name
-               << "' in global part of symbol table";
+      // MIPSpro-built shared objects -- every IRIX system library -- list
+      // their sections in .dynsym as local STT_SECTION symbols, which rld
+      // relocates against. Not ours to import; skip them quietly.
+      if (!(ctx.arg.osabi == ELFOSABI_IRIX && sym.getType() == STT_SECTION))
+        Err(ctx) << this << ": invalid local symbol '" << name
+                 << "' in global part of symbol table";
       continue;
     }
 
@@ -1819,6 +1823,11 @@ BitcodeFile::BitcodeFile(Ctx &ctx, MemoryBufferRef mb, StringRef archiveName,
 
   Triple t(obj->getTargetTriple());
   ekind = getBitcodeELFKind(t);
+  // IRIX: a 64-bit MIPS triple is compiled for n32 (ELF32) or n64, which the
+  // triple does not say; the driver says it with the emulation instead.
+  if (t.isOSIRIX() && t.isMIPS64() && ctx.arg.osabi == ELFOSABI_IRIX &&
+      ctx.arg.ekind != ELFNoneKind)
+    ekind = ctx.arg.ekind;
   emachine = getBitcodeMachineKind(ctx, mb.getBufferIdentifier(), t);
   osabi = getOsAbi(t);
 }
@@ -1968,11 +1977,269 @@ InputFile *elf::createInternalFile(Ctx &ctx, StringRef name) {
   return file;
 }
 
+// SGI's IRIX compilers and assemblers wrote relocatable objects that do not
+// conform to the ELF spec, and IRIX's static archives (/usr/lib32/libGLw.a,
+// for one) are full of them:
+//
+//  - the symbol table has sh_info = 0 and mixes local and global symbols,
+//    where ELF requires every local before the first global;
+//  - a section can have both a REL and a RELA relocation section (implicit
+//    addends for some types, explicit for others);
+//  - .MIPS.events.* and .MIPS.content.* (SHT_MIPS_EVENTS, SHT_MIPS_CONTENT)
+//    carry metadata for SGI's own tools, with relocation types of their own;
+//  - read-only gp-relative sections (.srdata, small read-only data reached
+//    through $gp). lld places a read-only section with the read-only data,
+//    far below .got, and puts _gp 0x7ff0 above the lowest gp-relative
+//    section, so every GOT access went out of range.
+//
+// Rather than teach the rest of lld about any of that, rewrite such an
+// object in memory into a conforming one before it is parsed: symbols
+// reordered locals-first (relocations renumbered to match), each REL section
+// that shares a target with a RELA section merged into it with its implicit
+// addends made explicit, the SGI metadata sections dropped (SHT_NULL, which
+// the parser skips, and with them the SGI debug information of an object that
+// has them), and gp-relative sections made writable so they sit with
+// .got and .sdata, inside $gp's reach, as on IRIX. A conforming object is
+// returned untouched.
+static constexpr uint32_t SHT_SGI_MIPS_CONTENT = 0x7000000c;
+static constexpr uint32_t SHT_SGI_MIPS_EVENTS = 0x70000021;
+
+// The implicit addend of a REL relocation that stands alone. Paired types
+// (HI16/LO16, GOT16) need their partner and are not converted.
+static std::optional<int64_t> sgiImplicitAddend(uint32_t type,
+                                                const uint8_t *loc) {
+  uint32_t word = read32be(loc);
+  switch (type) {
+  case R_MIPS_NONE:
+  case R_MIPS_JALR:
+    return 0;
+  case R_MIPS_32:
+  case R_MIPS_GPREL32:
+    return SignExtend64<32>(word);
+  case R_MIPS_26:
+    return SignExtend64<28>(word << 2);
+  case R_MIPS_GPREL16:
+  case R_MIPS_LITERAL:
+  case R_MIPS_CALL16:
+  case R_MIPS_GOT_DISP:
+  case R_MIPS_GOT_PAGE:
+  case R_MIPS_GOT_OFST:
+    return SignExtend64<16>(word);
+  default:
+    return std::nullopt;
+  }
+}
+
+template <class ELFT>
+static MemoryBufferRef normalizeSgiObject(Ctx &ctx, MemoryBufferRef mb) {
+  using Ehdr = typename ELFT::Ehdr;
+  using Shdr = typename ELFT::Shdr;
+  using Sym = typename ELFT::Sym;
+  using Rel = typename ELFT::Rel;
+  using Rela = typename ELFT::Rela;
+  const auto *eh = reinterpret_cast<const Ehdr *>(mb.getBufferStart());
+  if (eh->e_type != ET_REL || eh->e_machine != EM_MIPS)
+    return mb;
+  Expected<ELFFile<ELFT>> objOrErr = ELFFile<ELFT>::create(mb.getBuffer());
+  if (!objOrErr) {
+    consumeError(objOrErr.takeError());
+    return mb;
+  }
+  ELFFile<ELFT> &obj = *objOrErr;
+  Expected<typename ELFT::ShdrRange> secsOrErr = obj.sections();
+  if (!secsOrErr) {
+    consumeError(secsOrErr.takeError());
+    return mb;
+  }
+  ArrayRef<Shdr> secs = *secsOrErr;
+  size_t symtabIdx = 0;
+  for (size_t i = 0; i != secs.size(); ++i)
+    if (secs[i].sh_type == SHT_SYMTAB)
+      symtabIdx = i;
+  if (!symtabIdx)
+    return mb;
+  const Shdr &symtab = secs[symtabIdx];
+  if (symtab.sh_entsize != sizeof(Sym) || symtab.sh_size % sizeof(Sym) ||
+      symtab.sh_offset + symtab.sh_size > mb.getBufferSize())
+    return mb;
+  ArrayRef<Sym> syms(
+      reinterpret_cast<const Sym *>(mb.getBufferStart() + symtab.sh_offset),
+      symtab.sh_size / sizeof(Sym));
+  if (syms.empty())
+    return mb;
+
+  // What needs doing.
+  bool reorder = symtab.sh_info == 0;
+  bool seenGlobal = false;
+  for (size_t i = 1; i != syms.size(); ++i) {
+    if (syms[i].getBinding() != STB_LOCAL)
+      seenGlobal = true;
+    else if (seenGlobal)
+      reorder = true;
+  }
+  DenseMap<uint32_t, size_t> relOf, relaOf; // target section -> reloc section
+  bool sgiMeta = false, sgiEvents = false;
+  for (size_t i = 0; i != secs.size(); ++i) {
+    uint32_t t = secs[i].sh_type;
+    uint64_t f = secs[i].sh_flags;
+    if (t == SHT_SGI_MIPS_EVENTS || t == SHT_SGI_MIPS_CONTENT)
+      sgiEvents = true;
+    if (t == SHT_SGI_MIPS_EVENTS || t == SHT_SGI_MIPS_CONTENT ||
+        ((f & SHF_ALLOC) && (f & SHF_MIPS_GPREL) && !(f & SHF_WRITE)))
+      sgiMeta = true;
+    else if ((t == SHT_REL || t == SHT_RELA) && secs[i].sh_link == symtabIdx)
+      (t == SHT_REL ? relOf : relaOf)[secs[i].sh_info] = i;
+  }
+  bool merge = false;
+  for (auto &[target, idx] : relOf)
+    if (relaOf.count(target))
+      merge = true;
+  if (!reorder && !merge && !sgiMeta)
+    return mb;
+
+  // The new object: the original bytes, then merged RELA sections, then a
+  // new section header table.
+  size_t size = alignTo(mb.getBufferSize(), 8);
+  SmallVector<std::pair<uint32_t, size_t>> merged; // RELA index -> new offset
+  for (size_t relIdx = 0; relIdx != secs.size(); ++relIdx) {
+    if (secs[relIdx].sh_type != SHT_REL || secs[relIdx].sh_link != symtabIdx)
+      continue;
+    auto it = relaOf.find(secs[relIdx].sh_info);
+    if (it == relaOf.end())
+      continue;
+    size_t n = secs[relIdx].sh_size / sizeof(Rel) +
+               secs[it->second].sh_size / sizeof(Rela);
+    merged.push_back({it->second, size});
+    size = alignTo(size + n * sizeof(Rela), 8);
+  }
+  size_t shoff = size;
+  size += secs.size() * sizeof(Shdr);
+  auto *buf = static_cast<uint8_t *>(bAlloc().Allocate(size, Align(8)));
+  memset(buf, 0, size);
+  memcpy(buf, mb.getBufferStart(), mb.getBufferSize());
+  auto *newShdrs = reinterpret_cast<Shdr *>(buf + shoff);
+  for (size_t i = 0; i != secs.size(); ++i)
+    newShdrs[i] = secs[i];
+  reinterpret_cast<Ehdr *>(buf)->e_shoff = shoff;
+
+  // Symbols, locals first.
+  std::vector<uint32_t> newIndex(syms.size());
+  std::vector<Sym> order;
+  order.reserve(syms.size());
+  order.push_back(syms[0]);
+  for (int pass = 0; pass != 2; ++pass)
+    for (size_t i = 1; i != syms.size(); ++i)
+      if ((syms[i].getBinding() == STB_LOCAL) == (pass == 0)) {
+        newIndex[i] = order.size();
+        order.push_back(syms[i]);
+      }
+  uint32_t firstGlobal = 1;
+  while (firstGlobal != order.size() &&
+         order[firstGlobal].getBinding() == STB_LOCAL)
+    ++firstGlobal;
+  memcpy(buf + symtab.sh_offset, order.data(), order.size() * sizeof(Sym));
+  newShdrs[symtabIdx].sh_info = firstGlobal;
+
+  // Relocations: symbols renumbered in place, in every section. An index
+  // past the table is left alone, for the parser to report.
+  auto renumber = [&](uint32_t sym) {
+    return sym < newIndex.size() ? newIndex[sym] : sym;
+  };
+  for (size_t i = 0; i != secs.size(); ++i) {
+    if (secs[i].sh_link != symtabIdx)
+      continue;
+    if (secs[i].sh_type == SHT_REL) {
+      auto *r = reinterpret_cast<Rel *>(buf + secs[i].sh_offset);
+      for (size_t j = 0, e = secs[i].sh_size / sizeof(Rel); j != e; ++j)
+        r[j].setSymbolAndType(renumber(r[j].getSymbol(false)),
+                              r[j].getType(false), false);
+    } else if (secs[i].sh_type == SHT_RELA) {
+      auto *r = reinterpret_cast<Rela *>(buf + secs[i].sh_offset);
+      for (size_t j = 0, e = secs[i].sh_size / sizeof(Rela); j != e; ++j)
+        r[j].setSymbolAndType(renumber(r[j].getSymbol(false)),
+                              r[j].getType(false), false);
+    }
+  }
+
+  // REL sections that share a target with a RELA section: merged into it,
+  // the implicit addends read from the target section's contents.
+  for (auto &[relaIdx, off] : merged) {
+    uint32_t target = secs[relaIdx].sh_info;
+    size_t relIdx = relOf[target];
+    std::vector<Rela> out;
+    auto *ra = reinterpret_cast<const Rela *>(buf + secs[relaIdx].sh_offset);
+    out.assign(ra, ra + secs[relaIdx].sh_size / sizeof(Rela));
+    auto *rl = reinterpret_cast<const Rel *>(buf + secs[relIdx].sh_offset);
+    const Shdr &tsec = secs[target];
+    for (size_t j = 0, e = secs[relIdx].sh_size / sizeof(Rel); j != e; ++j) {
+      uint32_t type = rl[j].getType(false);
+      if (rl[j].r_offset + 4 > tsec.sh_size) {
+        Err(ctx) << mb.getBufferIdentifier()
+                 << ": SGI object: REL relocation past the end of section "
+                 << target;
+        return mb;
+      }
+      std::optional<int64_t> a =
+          sgiImplicitAddend(type, buf + tsec.sh_offset + rl[j].r_offset);
+      if (!a) {
+        Err(ctx) << mb.getBufferIdentifier()
+                 << ": SGI object: cannot merge a REL relocation of type "
+                 << type << " into RELA";
+        return mb;
+      }
+      Rela n;
+      n.r_offset = rl[j].r_offset;
+      n.r_info = rl[j].r_info;
+      n.r_addend = *a;
+      out.push_back(n);
+    }
+    // Relocations at one offset stay consecutive and in order: MIPS composes
+    // them (GPREL16 + SUB + HI16).
+    std::stable_sort(out.begin(), out.end(), [](const Rela &a, const Rela &b) {
+      return a.r_offset < b.r_offset;
+    });
+    memcpy(buf + off, out.data(), out.size() * sizeof(Rela));
+    newShdrs[relaIdx].sh_offset = off;
+    newShdrs[relaIdx].sh_size = out.size() * sizeof(Rela);
+    newShdrs[relIdx].sh_type = SHT_NULL;
+  }
+
+  // SGI's metadata sections and their relocations: dropped. So is the debug
+  // information of an object MIPSpro made (it has the metadata): an SGI
+  // DWARF 2 dialect that LLVM's reader warns about whenever lld looks up a
+  // source location for a diagnostic, and that nothing here can use.
+  auto dropped = [&](uint32_t t) {
+    return t == SHT_SGI_MIPS_EVENTS || t == SHT_SGI_MIPS_CONTENT ||
+           (sgiEvents && t == SHT_MIPS_DWARF);
+  };
+  for (size_t i = 0; i != secs.size(); ++i) {
+    uint32_t t = secs[i].sh_type;
+    bool meta = dropped(t);
+    if (!meta && (t == SHT_REL || t == SHT_RELA) && secs[i].sh_info &&
+        secs[i].sh_info < secs.size())
+      meta = dropped(secs[secs[i].sh_info].sh_type);
+    if (meta) {
+      newShdrs[i].sh_type = SHT_NULL;
+      newShdrs[i].sh_flags = 0;
+    } else if ((secs[i].sh_flags & SHF_ALLOC) &&
+               (secs[i].sh_flags & SHF_MIPS_GPREL)) {
+      newShdrs[i].sh_flags |= SHF_WRITE;
+    }
+  }
+  return MemoryBufferRef(StringRef(reinterpret_cast<const char *>(buf), size),
+                         mb.getBufferIdentifier());
+}
+
 std::unique_ptr<ELFFileBase> elf::createObjFile(Ctx &ctx, MemoryBufferRef mb,
                                                 StringRef archiveName,
                                                 bool lazy) {
   std::unique_ptr<ELFFileBase> f;
-  switch (getELFKind(ctx, mb, archiveName)) {
+  ELFKind kind = getELFKind(ctx, mb, archiveName);
+  if (kind == ELF32BEKind)
+    mb = normalizeSgiObject<ELF32BE>(ctx, mb);
+  else if (kind == ELF64BEKind)
+    mb = normalizeSgiObject<ELF64BE>(ctx, mb);
+  switch (kind) {
   case ELF32LEKind:
     f = std::make_unique<ObjFile<ELF32LE>>(ctx, ELF32LEKind, mb, archiveName);
     break;
