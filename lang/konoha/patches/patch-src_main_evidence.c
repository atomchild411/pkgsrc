$NetBSD: patch-src_main_evidence.c,v 1.2 2012/08/12 11:24:00 marino Exp $

* Resolve conflict of si_code on NetBSD
* Don't use K_USING_BSD to load sys/siginfo.h.  Fails for DFly/FreeBSD.
IRIX: no tm_gmtoff; use timezone/altzone.

--- src/main/evidence.c.orig
+++ src/main/evidence.c
@@ -37,6 +37,10 @@
 #include<unistd.h>
 #endif
 
+#if defined(__NetBSD__)
+#include <sys/siginfo.h>
+#endif
+
 #if defined(HAVE_LIBMEMCACHED)
 #include <libmemcached/memcached.h>
 #endif
@@ -85,6 +89,8 @@
 #if defined(K_USING_WINDOWS_)
 	_tzset();
 	int gmtoff = (int)(_timezone / (60 * 60));
+#elif defined(__sgi) /* IRIX: no tm_gmtoff */
+	int gmtoff = (int)(-(tmp->tm_isdst > 0 ? altzone : timezone) / (60 * 60));
 #else
 	int gmtoff = (int)(tmp->tm_gmtoff / (60 * 60));
 #endif /* defined(K_USING_WINDOWS_) */
@@ -600,11 +606,11 @@
 	record_signal(ctx, sig RECDATA);
 	if(ctx != NULL) {
 #if defined(K_USING_MINGW_)
-		int si_code = 0;
+		int si_code_ = 0;
 #else
-		int si_code = (si->si_code < 9) ? si->si_code : 0;
+		int si_code_ = (si->si_code < 9) ? si->si_code : 0;
 #endif /* defined(K_USING_MINGW_) */
-		THROW_Arithmetic(ctx, NULL, emsg[si_code]);
+		THROW_Arithmetic(ctx, NULL, emsg[si_code_]);
 	}
 }
 
@@ -642,12 +648,12 @@
 	record_signal(ctx, sig RECDATA);
 	if(ctx != NULL) {
 #if defined(K_USING_MINGW_)
-		int si_code = 0;
+		int si_code_ = 0;
 #else
-		int si_code = (si->si_code < 9) ? si->si_code : 0;
+		int si_code_ = (si->si_code < 9) ? si->si_code : 0;
 #endif /* defined(K_USING_MINGW_) */
 		WCTX(ctx)->signal = sig;
-		THROW_Halt(ctx, NULL, emsg[si_code]);
+		THROW_Halt(ctx, NULL, emsg[si_code_]);
 	}
 	_Exit(EX_SOFTWARE);
 }
@@ -663,9 +669,9 @@
 	CTX ctx = knh_getCurrentContext();
 	record_signal(ctx, sig RECDATA);
 	if(ctx != NULL) {
-		int si_code = (si->si_code < 4) ? si->si_code : 1;
+		int si_code_ = (si->si_code < 4) ? si->si_code : 1;
 		WCTX(ctx)->signal = sig;
-		THROW_Halt(ctx, NULL, emsg[si_code]);
+		THROW_Halt(ctx, NULL, emsg[si_code_]);
 	}
 	_Exit(EX_SOFTWARE);
 }
