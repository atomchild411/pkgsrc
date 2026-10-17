$NetBSD$

MIPS (IRIX): clang compiles neither __builtin_frame_address nor __builtin_return_address beyond the current frame; NSFrameAddress and NSReturnAddress give 0 there and NSCountFrames counts none (backtraces come from the unwinder).

--- Source/NSException.m.orig
+++ Source/NSException.m
@@ -639,6 +639,18 @@
 case a: env->addr = (__builtin_frame_address(a + 1) ? \
 __builtin_extract_return_address(__builtin_return_address(a + 1)) : 0); break;
 
+#if defined(__mips__)
+/* MIPS keeps no frame chain to walk: clang compiles neither
+ * __builtin_frame_address nor __builtin_return_address beyond the current
+ * frame. There are no addresses to give, nor frames to count (below);
+ * backtraces come from the unwinder (WITH_UNWIND).
+ */
+#undef _NS_FRAME_HACK
+#undef _NS_RETURN_HACK
+#define _NS_FRAME_HACK(a) case a: env->addr = 0; break;
+#define _NS_RETURN_HACK(a) case a: env->addr = 0; break;
+#endif
+
 /*
  * The following horrible signal handling code is a workaround for the fact
  * that the __builtin_frame_address() and __builtin_return_address()
@@ -784,6 +796,10 @@
 
 #define _NS_COUNT_HACK(X) if (__builtin_frame_address(X + 1) == 0) \
         goto done; else env->addr = (void*)(X + 1);
+#if defined(__mips__)
+#undef _NS_COUNT_HACK
+#define _NS_COUNT_HACK(X) goto done
+#endif
 
       _NS_COUNT_HACK(0); _NS_COUNT_HACK(1); _NS_COUNT_HACK(2);
       _NS_COUNT_HACK(3); _NS_COUNT_HACK(4); _NS_COUNT_HACK(5);
