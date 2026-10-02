$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- clang: IRIX target info and toolchain driver

--- lib/Driver/Driver.cpp.orig
+++ lib/Driver/Driver.cpp
@@ -37,6 +37,7 @@
 #include "ToolChains/MinGW.h"
 #include "ToolChains/MipsLinux.h"
 #include "ToolChains/NaCl.h"
+#include "ToolChains/IRIX.h"
 #include "ToolChains/NetBSD.h"
 #include "ToolChains/OHOS.h"
 #include "ToolChains/OpenBSD.h"
@@ -6815,6 +6816,9 @@ const ToolChain &Driver::getToolChain(const ArgList &Args,
     case llvm::Triple::NetBSD:
       TC = std::make_unique<toolchains::NetBSD>(*this, Target, Args);
       break;
+    case llvm::Triple::IRIX:
+      TC = std::make_unique<toolchains::IRIX>(*this, Target, Args);
+      break;
     case llvm::Triple::FreeBSD:
       if (Target.isPPC())
         TC = std::make_unique<toolchains::PPCFreeBSDToolChain>(*this, Target,
