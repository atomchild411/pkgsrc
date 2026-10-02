$NetBSD$

IRIX support (from the IRIX port of LLVM, atomchild411/llvm-project
branch iris/main):
- Build LLVM, clang and lld to run on IRIX

--- lib/Support/Unix/Program.inc.orig
+++ lib/Support/Unix/Program.inc
@@ -335,7 +335,7 @@ static bool Execute(ProcessInfo &PI, StringRef Program,
 namespace llvm {
 namespace sys {
 
-#if defined(_AIX)
+#if defined(_AIX) || defined(__sgi)
 static pid_t(wait4)(pid_t pid, int *status, int options, struct rusage *usage);
 #elif !defined(__Fuchsia__)
 using ::wait4;
@@ -344,6 +344,16 @@ using ::wait4;
 } // namespace sys
 } // namespace llvm
 
+#ifdef __sgi
+// IRIX has no wait4: wait with waitpid, and report no resource usage.
+pid_t(llvm::sys::wait4)(pid_t pid, int *status, int options,
+                        struct rusage *usage) {
+  if (usage)
+    memset(usage, 0, sizeof(*usage));
+  return ::waitpid(pid, status, options);
+}
+#endif
+
 #ifdef _AIX
 #ifndef _ALL_SOURCE
 extern "C" pid_t(wait4)(pid_t pid, int *status, int options,
@@ -489,7 +499,13 @@ ProcessInfo llvm::sys::Wait(const ProcessInfo &PI,
     }
   } else if (WIFSIGNALED(status)) {
     if (ErrMsg) {
+#ifdef __sgi
+      // IRIX has no strsignal.
+      int Sig = WTERMSIG(status);
+      *ErrMsg = Sig > 0 && Sig < _sys_nsig ? _sys_siglist[Sig] : "Unknown signal";
+#else
       *ErrMsg = strsignal(WTERMSIG(status));
+#endif
 #ifdef WCOREDUMP
       if (WCOREDUMP(status))
         *ErrMsg += " (core dumped)";
