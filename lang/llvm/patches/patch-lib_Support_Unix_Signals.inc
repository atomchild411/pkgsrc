$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Build LLVM, clang and lld to run on IRIX

--- lib/Support/Unix/Signals.inc.orig
+++ lib/Support/Unix/Signals.inc
@@ -852,7 +852,7 @@ void llvm::sys::PrintStackTrace(raw_ostream &OS, int Depth) {
   OS << "Stack dump without symbol names (ensure you have llvm-symbolizer in "
         "your PATH or set the environment var `LLVM_SYMBOLIZER_PATH` to point "
         "to it):\n";
-#if HAVE_DLOPEN && !defined(_AIX)
+#if HAVE_DLOPEN && !defined(_AIX) && !defined(__sgi) // IRIX: no dladdr
   int width = 0;
   for (int i = 0; i < depth; ++i) {
     Dl_info dlinfo;
