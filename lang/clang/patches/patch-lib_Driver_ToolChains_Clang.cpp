$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- R10000 scheduling model, CPUs r10000 to r16000, and -mtune

--- lib/Driver/ToolChains/Clang.cpp.orig
+++ lib/Driver/ToolChains/Clang.cpp
@@ -1931,6 +1931,13 @@ void Clang::AddMIPSTargetArgs(const ArgList &Args,
       CmdArgs.push_back("-mips-jalr-reloc=0");
     }
   }
+
+  // The processor to schedule for, apart from the instruction set: MIPS III
+  // code for R4400s tuned for an R10000, say.
+  if (const Arg *A = Args.getLastArg(options::OPT_mtune_EQ)) {
+    CmdArgs.push_back("-tune-cpu");
+    CmdArgs.push_back(A->getValue());
+  }
 }
 
 void Clang::AddPPCTargetArgs(const ArgList &Args,
