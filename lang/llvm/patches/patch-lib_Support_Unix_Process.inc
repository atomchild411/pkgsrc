$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Build LLVM, clang and lld to run on IRIX

--- lib/Support/Unix/Process.inc.orig
+++ lib/Support/Unix/Process.inc
@@ -430,4 +430,10 @@ unsigned llvm::sys::Process::GetRandomNumber() {
 #endif
 }
 
-[[noreturn]] void Process::ExitNoCleanup(int RetCode) { _Exit(RetCode); }
+[[noreturn]] void Process::ExitNoCleanup(int RetCode) {
+#ifdef __sgi
+  _exit(RetCode); // IRIX has no C99 _Exit
+#else
+  _Exit(RetCode);
+#endif
+}
