$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Driver: MIPSpro's options (-woff, -OPT:, -fullwarn, ...) accepted and ignored

--- include/clang/Driver/Options.td.orig
+++ include/clang/Driver/Options.td
@@ -314,6 +314,24 @@
 def mmpx : Flag<["-"], "mmpx">, Group<clang_ignored_legacy_options_Group>;
 def mno_mpx : Flag<["-"], "mno-mpx">, Group<clang_ignored_legacy_options_Group>;
 
+// MIPSpro, IRIX's own compiler: options that IRIX makefiles and build scripts
+// pass (-woff 1110, -OPT:Olimit=0, -fullwarn, -n32). The IRIX toolchain
+// accepts and ignores them; other targets report them unused.
+def irix_mipspro_Group : OptionGroup<"<IRIX MIPSpro options>">,
+  Flags<[Ignored]>;
+def : Separate<["-"], "woff">, Group<irix_mipspro_Group>;
+def : Flag<["-"], "fullwarn">, Group<irix_mipspro_Group>;
+def : Flag<["-"], "n32">, Group<irix_mipspro_Group>;
+def : Flag<["-"], "IPA">, Group<irix_mipspro_Group>;
+def : Joined<["-"], "CG:">, Group<irix_mipspro_Group>;
+def : Joined<["-"], "INLINE:">, Group<irix_mipspro_Group>;
+def : Joined<["-"], "IPA:">, Group<irix_mipspro_Group>;
+def : Joined<["-"], "LANG:">, Group<irix_mipspro_Group>;
+def : Joined<["-"], "LNO:">, Group<irix_mipspro_Group>;
+def : Joined<["-"], "OPT:">, Group<irix_mipspro_Group>;
+def : Joined<["-"], "TARG:">, Group<irix_mipspro_Group>;
+def : Joined<["-"], "TENV:">, Group<irix_mipspro_Group>;
+
 // Group that ignores all gcc optimizations that won't be implemented
 def clang_ignored_gcc_optimization_f_Group : OptionGroup<
   "<clang_ignored_gcc_optimization_f_Group>">, Group<f_Group>, Flags<[Ignored]>;
