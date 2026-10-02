$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- clang: IRIX target info and toolchain driver
- clang: wrapper headers for what IRIX's lack, and _WCHAR_T in C++
- clang: __IRIX_VERSION__, char * va_list, and C99 gaps in the headers
- clang: _LANGUAGE_ASSEMBLY for preprocessed assembly

--- lib/Basic/Targets/OSTargets.h.orig
+++ lib/Basic/Targets/OSTargets.h
@@ -428,6 +428,107 @@ public:
   }
 };
 
+// IRIX Target
+//
+// The predefines are MIPSpro 7.4's, as `cc -show` reports them on IRIX 6.5
+// for C and C++, n32 and 64, -mips3 and -mips4, shared and -non_shared: SGI's
+// headers gate nearly every declaration on them. Two are left out on
+// purpose: __INLINE_INTRINSICS selects MIPSpro-only #pragma intrinsic forms,
+// and __MATH_HAS_NO_SIDE_EFFECTS promises an errno behaviour we do not keep.
+// The ISA (__mips, _MIPS_ISA) comes from MipsTargetInfo.
+template <typename Target>
+class LLVM_LIBRARY_VISIBILITY IRIXTargetInfo : public OSTargetInfo<Target> {
+protected:
+  void getOSDefines(const LangOptions &Opts, const llvm::Triple &Triple,
+                    MacroBuilder &Builder) const override {
+    Builder.defineMacro("__sgi");
+    Builder.defineMacro("__unix");
+    Builder.defineMacro("__unix__");
+    Builder.defineMacro("__host_mips");
+    Builder.defineMacro("__ELF__");
+    Builder.defineMacro("__EXTENSIONS__");
+    Builder.defineMacro("_SGI_SOURCE");
+    Builder.defineMacro("_SVR4_SOURCE");
+    Builder.defineMacro("_SYSTYPE_SVR4");
+    Builder.defineMacro("_MODERN_C");
+    Builder.defineMacro("_LONGLONG");
+    Builder.defineMacro("_COMPILER_VERSION", "740");
+    Builder.defineMacro("_SGI_COMPILER_VERSION", "740");
+
+    // The IRIX release built for, from the triple (mips64-sgi-irix6.5.22),
+    // as 60522. With none given, 6.5.7, the oldest supported: what builds
+    // for it runs on every later 6.5 release. Headers use it to supply what
+    // older releases lack (see clang's irix_wrappers).
+    VersionTuple Version = Triple.getOSVersion();
+    unsigned Major = Version.getMajor() ? Version.getMajor() : 6;
+    unsigned Minor = Version.getMinor().value_or(5);
+    unsigned Release = Version.getSubminor().value_or(7);
+    Builder.defineMacro("__IRIX_VERSION__",
+                        Twine(Major * 10000 + Minor * 100 + Release));
+    if (Opts.GNUMode) {
+      // MIPSpro also defines these in the user's namespace.
+      Builder.defineMacro("sgi");
+      Builder.defineMacro("unix");
+      Builder.defineMacro("host_mips");
+    }
+
+    if (Opts.AsmPreprocessor) {
+      // Assembly (.S): SGI's headers keep their C declarations out of it
+      // behind _LANGUAGE_C, and give it what it may use under
+      // _LANGUAGE_ASSEMBLY, as MIPSpro's and IRIX gcc's drivers defined.
+      Builder.defineMacro("_LANGUAGE_ASSEMBLY");
+      if (Opts.GNUMode)
+        Builder.defineMacro("LANGUAGE_ASSEMBLY");
+    } else if (Opts.CPlusPlus) {
+      Builder.defineMacro("_LANGUAGE_C_PLUS_PLUS", "1");
+      // wchar_t is built in: the guard SGI's headers check before declaring
+      // their own (a C typedef, illegal in C++).
+      Builder.defineMacro("_WCHAR_T");
+    } else {
+      Builder.defineMacro("_LANGUAGE_C");
+      if (Opts.GNUMode)
+        Builder.defineMacro("LANGUAGE_C");
+    }
+
+    // The sizes MIPSpro gives beside _MIPS_SZINT and friends.
+    Builder.defineMacro("_SIZE_INT", Twine(this->getIntWidth()));
+    Builder.defineMacro("_SIZE_LONG", Twine(this->getLongWidth()));
+    Builder.defineMacro("_SIZE_PTR",
+                        Twine(this->getPointerWidth(LangAS::Default)));
+
+    // Position-independent code, which is the default: MIPSpro drops these
+    // under -non_shared.
+    if (Opts.PICLevel) {
+      Builder.defineMacro("_PIC");
+      Builder.defineMacro("__DSO__");
+    }
+
+    // MIPSpro sets __c99 only under -c99. It gates IRIX's C99 headers
+    // (<stdint.h> #errors without it) and C++'s <cstdint> needs them too.
+    if (Opts.C99 || Opts.CPlusPlus)
+      Builder.defineMacro("__c99");
+
+    // IRIX's <stdarg.h> is MIPSpro-only (__builtin_classof), so clang's
+    // stands in; _VA_LIST_ is the guard SGI's headers use to leave va_list
+    // alone. Both say char * (see getBuiltinVaListKind).
+    Builder.defineMacro("_VA_LIST_");
+
+    if (Opts.POSIXThreads)
+      Builder.defineMacro("_REENTRANT");
+  }
+
+public:
+  IRIXTargetInfo(const llvm::Triple &Triple, const TargetOptions &Opts)
+      : OSTargetInfo<Target>(Triple, Opts) {}
+
+  // va_list is char * on IRIX, as MIPSpro has it and as every prototype in
+  // SGI's headers spells it (vfprintf(FILE *, const char *, char *)); the
+  // MIPS default, void *, does not convert to that in C++.
+  TargetInfo::BuiltinVaListKind getBuiltinVaListKind() const override {
+    return TargetInfo::CharPtrBuiltinVaList;
+  }
+};
+
 // NetBSD Target
 template <typename Target>
 class LLVM_LIBRARY_VISIBILITY NetBSDTargetInfo : public OSTargetInfo<Target> {
