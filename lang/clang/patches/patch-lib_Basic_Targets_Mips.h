$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- R10000 scheduling model, CPUs r10000 to r16000, and -mtune
- long double is a double
- wchar_t, wint_t and intptr_t are long where long is 32 bits

--- lib/Basic/Targets/Mips.h.orig
+++ lib/Basic/Targets/Mips.h
@@ -132,12 +132,28 @@ public:
     PtrDiffType = IntPtrType = SignedInt;
     SizeType = UnsignedInt;
     SuitableAlign = 64;
+    setIRIXLong32Types();
+  }
+
+  // IRIX's headers, wherever long is 32 bits (o32 and n32), make wchar_t,
+  // wint_t and intptr_t long, as GCC's IRIX port did: the same size as int,
+  // but a type of its own, so L"" and __INTPTR_TYPE__ have to agree.
+  void setIRIXLong32Types() {
+    if (getTriple().isOSIRIX()) {
+      WCharType = WIntType = SignedLong;
+      IntPtrType = SignedLong;
+    }
   }
 
   void setN32N64ABITypes() {
     LongDoubleWidth = LongDoubleAlign = 128;
     LongDoubleFormat = &llvm::APFloat::IEEEquad();
-    if (getTriple().isOSFreeBSD()) {
+    // IRIX: double too. IRIX's own long double (MIPSpro's n32/n64) is a
+    // pair of doubles that clang cannot represent; IEEE quad there meant
+    // that every long double crossing into libc (printf %Lf, scanf, strtold,
+    // libm's *l) was misread. clang's IRIX wrappers and CodeGen's builtin
+    // names send those through the double functions instead.
+    if (getTriple().isOSFreeBSD() || getTriple().isOSIRIX()) {
       LongDoubleWidth = LongDoubleAlign = 64;
       LongDoubleFormat = &llvm::APFloat::IEEEdouble();
     }
@@ -167,6 +183,7 @@ public:
     PointerWidth = PointerAlign = 32;
     PtrDiffType = IntPtrType = SignedInt;
     SizeType = UnsignedInt;
+    setIRIXLong32Types();
   }
 
   bool isValidCPUName(StringRef Name) const override;
@@ -188,6 +205,9 @@ public:
       Features["mips64r2"] = Features["cnmips"] = true;
     else if (CPU == "octeon+")
       Features["mips64r2"] = Features["cnmips"] = Features["cnmipsp"] = true;
+    else if (CPU == "r10000" || CPU == "r12000" || CPU == "r14000" ||
+             CPU == "r16000")
+      Features["mips4"] = true;
     else
       Features[CPU] = true;
     return TargetInfo::initFeatureMap(Features, Diags, CPU, FeaturesVec);
