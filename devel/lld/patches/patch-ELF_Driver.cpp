$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts
- [IRIX] Accept GNU ld's IRIX emulation names

--- ELF/Driver.cpp.orig
+++ ELF/Driver.cpp
@@ -152,6 +152,10 @@ static std::tuple<ELFKind, uint16_t, uint8_t> parseEmulation(Ctx &ctx,
   if (s.ends_with("_fbsd")) {
     s = s.drop_back(5);
     osabi = ELFOSABI_FREEBSD;
+  } else if (s.ends_with("_irix")) {
+    // Output for IRIX's runtime linker, rld (see ELFOSABI_IRIX uses).
+    s = s.drop_back(5);
+    osabi = ELFOSABI_IRIX;
   }
 
   std::pair<ELFKind, uint16_t> ret =
@@ -1865,7 +1869,19 @@ static void readConfigs(Ctx &ctx, opt::InputArgList &args) {
            "intend to set the base address";
 
   // Parse ELF{32,64}{LE,BE} and CPU type.
-  if (auto *arg = args.getLastArg(OPT_m)) {
+  // GNU ld's IRIX emulations (elf32bsmip, elf32bmipn32, elf64bmip, and their
+  // little-endian twins) name an ABI that the input objects already carry,
+  // and libtool picks them by matching file(1) output, which says "32-bit"
+  // for n32 too. Take the ABI from the inputs, as without -m.
+  auto isIrixEmulation = [](StringRef s) {
+    return StringSwitch<bool>(s)
+        .Cases("elf32bsmip", "elf32lsmip", "elf32bmipn32", "elf32lmipn32",
+               true)
+        .Cases("elf64bmip", "elf64lmip", true)
+        .Default(false);
+  };
+  if (auto *arg = args.getLastArg(OPT_m);
+      arg && !isIrixEmulation(arg->getValue())) {
     StringRef s = arg->getValue();
     std::tie(ctx.arg.ekind, ctx.arg.emachine, ctx.arg.osabi) =
         parseEmulation(ctx, s);
@@ -2508,6 +2524,34 @@ static void writeDependencyFile(Ctx &ctx) {
   }
 }
 
+// IRIX's rld looks up __Argc and __Argv (commons in crt1.o), __start and
+// __rld_obj_head in every executable, and fails if one has no .dynsym entry
+// with a GOT slot; SpeedShop needs __start there too.
+static void markIRIXRldSymbols(Ctx &ctx) {
+  if (ctx.arg.osabi != ELFOSABI_IRIX || ctx.arg.shared)
+    return;
+  for (StringRef name : {"__Argc", "__Argv", "__start", "__rld_obj_head"})
+    if (Symbol *sym = ctx.symtab->find(name))
+      sym->inDynamicList = true;
+}
+
+// __rld_obj_head, a common in crt1.o, must point at .rld.map, which rld
+// fills in with its list of loaded objects.
+static void defineIRIXRldObjHead(Ctx &ctx) {
+  if (ctx.arg.osabi != ELFOSABI_IRIX || ctx.arg.shared || !ctx.in.mipsRldMap)
+    return;
+  Symbol *sym = ctx.symtab->find("__rld_obj_head");
+  if (!sym)
+    return;
+  Defined(ctx, ctx.internalFile, StringRef(), STB_GLOBAL, STV_DEFAULT,
+          STT_OBJECT, /*value=*/0, /*size=*/ctx.arg.wordsize,
+          ctx.in.mipsRldMap.get())
+      .overwrite(*sym);
+  sym->inDynamicList = true;
+  sym->isExported = true;
+  sym->isPreemptible = true;
+}
+
 // Replaces common symbols with defined symbols reside in .bss sections.
 // This function is called after all symbol names are resolved. As a
 // result, the passes after the symbol resolution won't see any
@@ -3144,6 +3188,12 @@ template <class ELFT> void LinkerDriver::link(opt::InputArgList &args) {
   for (StringRef name : ctx.arg.undefined)
     ctx.symtab->addUnusedUndefined(name)->referenced = true;
 
+  // IRIX executables always define these: libc takes the start of its heap
+  // from _end, and rld and the tools read the others.
+  if (ctx.arg.osabi == ELFOSABI_IRIX && !ctx.arg.shared)
+    for (StringRef name : {"_etext", "etext", "_end", "end"})
+      ctx.symtab->addUnusedUndefined(name)->referenced = true;
+
   parseFiles(ctx, files);
 
   // Create dynamic sections for dynamic linking and static PIE.
@@ -3261,6 +3311,7 @@ template <class ELFT> void LinkerDriver::link(opt::InputArgList &args) {
     llvm::TimeTraceScope timeScope("Process symbol versions");
     ctx.symtab->scanVersionScript();
 
+    markIRIXRldSymbols(ctx);
     parseVersionAndComputeIsPreemptible(ctx);
   }
 
@@ -3439,6 +3490,7 @@ template <class ELFT> void LinkerDriver::link(opt::InputArgList &args) {
   // Create synthesized sections such as .got and .plt. This is called before
   // processSectionCommands() so that they can be placed by SECTIONS commands.
   createSyntheticSections<ELFT>(ctx);
+  defineIRIXRldObjHead(ctx);
 
   // Some input sections that are used for exception handling need to be moved
   // into synthetic sections. Do that now so that they aren't assigned to
