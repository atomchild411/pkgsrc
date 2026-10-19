$NetBSD: patch-iozone.c,v 1.1 2022/05/28 11:39:57 adam Exp $

Support DragonFly.
pthread_barrierattr_setpshared() is hidden on NetBSD.
IRIX: no sighandler_t (use my_sig_t as the BSDs do), and include <errno.h>.

--- iozone.c.orig
+++ iozone.c
@@ -74,7 +74,7 @@
 #include <windows.h>
 #include <errno.h>
 #else
-#if defined(linux) || defined(solaris) || defined(IOZ_macosx) || defined(__AIX__) || defined(__FreeBSD__) || defined(_HPUX_SOURCE) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__NetBSD__)
+#if defined(linux) || defined(solaris) || defined(IOZ_macosx) || defined(__AIX__) || defined(__FreeBSD__) || defined(_HPUX_SOURCE) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(__sgi)
 #include <errno.h>
 #else
 extern  int errno;   /* imported for errors */
@@ -296,7 +296,7 @@
 #include <stdio.h>
 #include <signal.h>
 
-#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows)
+#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows) || defined(__sgi)
   #ifndef my_sig_t
   typedef void (*my_sig_t)(int);
   #endif
@@ -475,6 +475,9 @@
 struct iovec piov[PVECMAX];
 #define piov_base iov_base
 #define piov_len iov_len
+#if defined (__DragonFly__)
+#define DFLY_VECTOR_OFFSET
+#endif
 #endif
 
 #endif
@@ -1032,7 +1035,7 @@
 void begin(off64_t,long long);
 void record_command_line(int, char **);
 void show_help(void);		/* show development help          */
-#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows)
+#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows) || defined(__sgi)
 my_sig_t signal_handler(void);	/* clean up if user interrupts us */
 #else
 sighandler_t signal_handler(void);	/* clean up if user interrupts us */
@@ -1150,7 +1153,7 @@
 void begin();
 void record_command_line();
 void show_help();
-#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows)
+#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows) || defined(__sgi)
 my_sig_t signal_handler(); /* clean up if user interrupts us */
 #else
 sighandler_t signal_handler(); /* clean up if user interrupts us */
@@ -1925,7 +1928,7 @@
 	argvsave=argv;
 
 #ifndef NO_SIGNAL
-#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows)
+#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows) || defined(__sgi)
     	signal((int) SIGINT, (my_sig_t) signal_handler);   /* handle user interrupt */
     	signal((int) SIGTERM, (my_sig_t) signal_handler);  /* handle kill from shell */
 #else
@@ -3730,13 +3733,13 @@
 
 ******************************************************************/
 #ifdef HAVE_ANSIC_C
-#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows)
+#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows) || defined(__sgi)
 my_sig_t signal_handler(void)
 #else
 sighandler_t signal_handler(void)
 #endif
 #else
-#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows)
+#if defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__APPLE__) || defined(__DragonFly__) || defined(__NetBSD__) || defined(solaris) || defined(Windows) || defined(__sgi)
 my_sig_t signal_handler()
 #else
 sighandler_t signal_handler()
@@ -3971,13 +3974,17 @@
 	if(use_thread)
 	{
 		barrier = (pthread_barrier_t*)alloc_mem(sizeof(pthread_barrier_t), 0); // Not shared
+#ifndef __NetBSD__
 		pthread_barrierattr_setpshared(&barrier_attr, PTHREAD_PROCESS_PRIVATE);
+#endif
 		pthread_barrier_init(barrier, &barrier_attr, num_child);
 	}
 	else
 	{
 		barrier = (pthread_barrier_t*)alloc_mem(sizeof(pthread_barrier_t), 1); // Shared
+#ifndef __NetBSD__
 		pthread_barrierattr_setpshared(&barrier_attr, PTHREAD_PROCESS_SHARED);
+#endif
 		pthread_barrier_init(barrier, &barrier_attr, num_child);
 	}
 
@@ -11429,7 +11436,7 @@
 					purgeit(piov[xx].piov_base,reclen);
 			}
 			if(pwritev(fd, piov,numvecs
-#ifndef PER_VECTOR_OFFSET
+#if defined(PER_VECTOR_OFFSET) || defined(DFLY_VECTOR_OFFSET)
 				, list_off[0]
 #endif
 				) != (reclen*numvecs))
@@ -11759,7 +11766,7 @@
 				   purgeit(piov[xx].piov_base,reclen);
 			}
 			if(preadv(fd, piov, numvecs
-#ifndef PER_VECTOR_OFFSET
+#if defined(PER_VECTOR_OFFSET) || defined(DFLY_VECTOR_OFFSET)
 				, list_off[0]
 #endif
 				) != (numvecs * reclen))
