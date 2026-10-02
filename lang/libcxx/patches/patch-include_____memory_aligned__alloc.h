$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- libc++: support IRIX 6.5

--- include/__memory/aligned_alloc.h.orig
+++ include/__memory/aligned_alloc.h
@@ -29,6 +29,10 @@ _LIBCPP_BEGIN_NAMESPACE_STD
 inline _LIBCPP_HIDE_FROM_ABI void* __libcpp_aligned_alloc(std::size_t __alignment, std::size_t __size) {
 #  if defined(_LIBCPP_MSVCRT_LIKE)
   return ::_aligned_malloc(__size, __alignment);
+#  elif defined(__sgi)
+  // IRIX has neither aligned_alloc nor posix_memalign, only memalign, whose
+  // memory free() takes back.
+  return ::memalign(__alignment, __size);
 #  elif _LIBCPP_STD_VER >= 17 && _LIBCPP_HAS_C11_ALIGNED_ALLOC
   // aligned_alloc() requires that __size is a multiple of __alignment,
   // but for C++ [new.delete.general], only states "if the value of an
