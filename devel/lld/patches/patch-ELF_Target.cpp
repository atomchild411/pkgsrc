$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- lld: output IRIX's runtime linker, rld, accepts

--- ELF/Target.cpp.orig
+++ ELF/Target.cpp
@@ -169,5 +169,5 @@ uint64_t TargetInfo::getImageBase() const {
   // Use --image-base if set. Fall back to the target default if not.
   if (ctx.arg.imageBase)
     return *ctx.arg.imageBase;
-  return ctx.arg.isPic ? 0 : defaultImageBase;
+  return ctx.arg.isPic ? defaultPicImageBase : defaultImageBase;
 }
