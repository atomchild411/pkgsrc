$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- clang: IRIX target info and toolchain driver

--- lib/Basic/Targets.cpp.orig
+++ lib/Basic/Targets.cpp
@@ -277,6 +277,8 @@ std::unique_ptr<TargetInfo> AllocateTarget(const llvm::Triple &Triple,
 
   case llvm::Triple::mips:
     switch (os) {
+    case llvm::Triple::IRIX:
+      return std::make_unique<IRIXTargetInfo<MipsTargetInfo>>(Triple, Opts);
     case llvm::Triple::Linux:
       return std::make_unique<LinuxTargetInfo<MipsTargetInfo>>(Triple, Opts);
     case llvm::Triple::RTEMS:
@@ -321,6 +323,8 @@ std::unique_ptr<TargetInfo> AllocateTarget(const llvm::Triple &Triple,
 
   case llvm::Triple::mips64:
     switch (os) {
+    case llvm::Triple::IRIX:
+      return std::make_unique<IRIXTargetInfo<MipsTargetInfo>>(Triple, Opts);
     case llvm::Triple::Linux:
       return std::make_unique<LinuxTargetInfo<MipsTargetInfo>>(Triple, Opts);
     case llvm::Triple::RTEMS:
