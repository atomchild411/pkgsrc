$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Build LLVM, clang and lld to run on IRIX

--- lib/Transforms/Scalar/LoopStrengthReduce.cpp.orig
+++ lib/Transforms/Scalar/LoopStrengthReduce.cpp
@@ -416,7 +416,7 @@ RegUseTracker::countRegister(const SCEV *Reg, size_t LUIdx) {
   RegSortData &RSD = Pair.first->second;
   if (Pair.second)
     RegSequence.push_back(Reg);
-  RSD.UsedByIndices.resize(std::max(RSD.UsedByIndices.size(), LUIdx + 1));
+  RSD.UsedByIndices.resize(std::max<size_t>(RSD.UsedByIndices.size(), LUIdx + 1));
   RSD.UsedByIndices.set(LUIdx);
 }
 
@@ -440,7 +440,7 @@ RegUseTracker::swapAndDropUse(size_t LUIdx, size_t LastLUIdx) {
     if (LUIdx < UsedByIndices.size())
       UsedByIndices[LUIdx] =
         LastLUIdx < UsedByIndices.size() ? UsedByIndices[LastLUIdx] : false;
-    UsedByIndices.resize(std::min(UsedByIndices.size(), LastLUIdx));
+    UsedByIndices.resize(std::min<size_t>(UsedByIndices.size(), LastLUIdx));
   }
 }
 
