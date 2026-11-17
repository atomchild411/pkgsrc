$NetBSD$

IRIX: no backtrace() there, so the crash handler printed only "No Backtrace on
this platform". Print the faulting address and pc, ra and sp from the signal
context, each with the loaded object it is in and the offset (dladdr).

--- neo/sys/posix/posix_main.cpp.orig
+++ neo/sys/posix/posix_main.cpp
@@ -563,6 +563,41 @@
 	raise(sig); // pass it on to system
 }
 
+#ifdef __sgi
+// IRIX has no backtrace(): report where it crashed from the signal context,
+// and which loaded object (dhewm3, or a game library) each address is in.
+#include <dlfcn.h>
+#include <sys/ucontext.h>
+
+static void crashPrintAddr(const char* what, unsigned long long a)
+{
+	Dl_info info;
+	if (a != 0 && dladdr((void*)(uintptr_t)a, &info) && info.dli_fname != NULL) {
+		CrashPrintf("  %-3s 0x%08llx  %s+0x%llx", what, a, info.dli_fname,
+		            a - (unsigned long long)(uintptr_t)info.dli_fbase);
+		if (info.dli_sname != NULL)
+			CrashPrintf(" (%s+0x%llx)", info.dli_sname,
+			            a - (unsigned long long)(uintptr_t)info.dli_saddr);
+		CrashPrintf("\n");
+	} else {
+		CrashPrintf("  %-3s 0x%08llx\n", what, a);
+	}
+}
+
+static void signalhandlerCrashInfo(int sig, siginfo_t* si, void* ctx)
+{
+	ucontext_t* uc = (ucontext_t*)ctx;
+	CrashPrintf("\n\nCrash context: signal %d, code %d, fault address %p\n", sig,
+	            si != NULL ? si->si_code : 0, si != NULL ? si->si_addr : NULL);
+	if (uc != NULL) {
+		crashPrintAddr("pc", (unsigned long long)uc->uc_mcontext.gregs[CTX_EPC]);
+		crashPrintAddr("ra", (unsigned long long)uc->uc_mcontext.gregs[CTX_RA]);
+		CrashPrintf("  sp  0x%08llx\n", (unsigned long long)uc->uc_mcontext.gregs[CTX_SP]);
+	}
+	signalhandlerCrash(sig);
+}
+#endif
+
 static bool disableTTYinput = false;
 
 static void signalhandlerConsoleStuff(int sig)
@@ -636,7 +671,15 @@
 
 	for(int i=0; i<sizeof(crashSigs)/sizeof(crashSigs[0]); ++i)
 	{
+#ifdef __sgi
+		struct sigaction sigact = {0};
+		sigact.sa_sigaction = signalhandlerCrashInfo;
+		sigemptyset(&sigact.sa_mask);
+		sigact.sa_flags = SA_RESTART|SA_RESETHAND|SA_SIGINFO;
+		sigaction(crashSigs[i], &sigact, NULL);
+#else
 		installSigHandler(crashSigs[i], SA_RESTART|SA_RESETHAND, signalhandlerCrash);
+#endif
 	}
 
 	installSigHandler(SIGTTIN, 0, signalhandlerConsoleStuff);
