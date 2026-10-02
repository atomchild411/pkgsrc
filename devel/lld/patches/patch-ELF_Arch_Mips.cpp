$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts
- lld: R_MIPS_LITERAL, R_MIPS_PJUMP, and .sbss before .bss

--- ELF/Arch/Mips.cpp.orig
+++ ELF/Arch/Mips.cpp
@@ -65,6 +65,13 @@ template <class ELFT> MIPS<ELFT>::MIPS(Ctx &ctx) : TargetInfo(ctx) {
     tlsModuleIndexRel = R_MIPS_TLS_DTPMOD32;
     tlsOffsetRel = R_MIPS_TLS_DTPREL32;
   }
+
+  // IRIX's rld will not take a shared object based at 0: use MIPSpro's
+  // bases for executables and shared objects.
+  if (ctx.arg.osabi == ELFOSABI_IRIX) {
+    defaultImageBase = 0x10000000;
+    defaultPicImageBase = 0x00400000;
+  }
 }
 
 template <class ELFT> uint32_t MIPS<ELFT>::calcEFlags() const {
@@ -98,7 +105,12 @@ RelExpr MIPS<ELFT>::getRelExpr(RelType type, const Symbol &s,
       return R_PC;
     return R_NONE;
   case R_MICROMIPS_JALR:
+  // A hint naming the target of a jump (SGI's compilers emit it); nothing to
+  // relocate.
+  case R_MIPS_PJUMP:
     return R_NONE;
+  // A gp-relative reference to a literal pool entry (.lit4, .lit8): GPREL16.
+  case R_MIPS_LITERAL:
   case R_MIPS_GPREL16:
   case R_MIPS_GPREL32:
   case R_MICROMIPS_GPREL16:
@@ -186,6 +198,9 @@ RelExpr MIPS<ELFT>::getRelExpr(RelType type, const Symbol &s,
   case R_MIPS_TLS_LDM:
   case R_MICROMIPS_TLS_LDM:
     return RE_MIPS_TLSLD;
+  // IRIX objects (crt1.o) carry section-displacement relocations in their
+  // .MIPS.events sections, for tools; nothing to do at link time.
+  case R_MIPS_SCN_DISP:
   case R_MIPS_NONE:
     return R_NONE;
   default:
@@ -389,6 +404,7 @@ int64_t MIPS<ELFT>::getImplicitAddend(const uint8_t *buf, RelType type) const {
   case R_MIPS_TLS_DTPREL32:
   case R_MIPS_TLS_DTPMOD32:
   case R_MIPS_TLS_TPREL32:
+  case R_MIPS_SCN_DISP:
     return SignExtend64<32>(read32(ctx, buf));
   case R_MIPS_26:
     // FIXME (simon): If the relocation target symbol is not a PLT entry
@@ -405,6 +421,7 @@ int64_t MIPS<ELFT>::getImplicitAddend(const uint8_t *buf, RelType type) const {
   case R_MIPS_CALL_LO16:
   case R_MIPS_GOT_LO16:
   case R_MIPS_GPREL16:
+  case R_MIPS_LITERAL:
   case R_MIPS_LO16:
   case R_MIPS_PCLO16:
   case R_MIPS_TLS_DTPREL_HI16:
@@ -625,6 +642,7 @@ void MIPS<ELFT>::relocate(uint8_t *loc, const Relocation &rel,
   case R_MIPS_GOT_DISP:
   case R_MIPS_GOT_PAGE:
   case R_MIPS_GPREL16:
+  case R_MIPS_LITERAL:
   case R_MIPS_TLS_GD:
   case R_MIPS_TLS_GOTTPREL:
   case R_MIPS_TLS_LDM:
