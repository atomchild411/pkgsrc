$NetBSD: patch-nspr_pr_src_pthreads_ptio.c,v 1.1 2026/05/19 08:48:15 jperkin Exp $

Fix for modern C.

IRIX port (pthreads, IPv4); NSPR dropped its old one.

--- nspr/pr/src/pthreads/ptio.c.orig
+++ nspr/pr/src/pthreads/ptio.c
@@ -72,7 +72,7 @@
 /*
  * extern ssize_t sendfilev(int, const struct sendfilevec *, int, size_t *);
  */
-static ssize_t (*pt_solaris_sendfilev_fptr)() = NULL;
+static ssize_t (*pt_solaris_sendfilev_fptr)(int, const struct sendfilevec *, int, size_t *) = NULL;
 
 #      define SOLARIS_SENDFILEV(a, b, c, d) \
         (*pt_solaris_sendfilev_fptr)((a), (b), (c), (d))
@@ -181,7 +181,7 @@
       defined(HPUX10_30) || defined(HPUX11) || defined(LINUX) ||    \
       defined(__GNU__) || defined(__GLIBC__) || defined(FREEBSD) || \
       defined(NETBSD) || defined(OPENBSD) || defined(NTO) ||        \
-      defined(DARWIN) || defined(RISCOS)
+      defined(DARWIN) || defined(RISCOS) || defined(IRIX)
 #    define _PRSelectFdSetArg_t fd_set*
 #  else
 #    error "Cannot determine architecture"
@@ -2368,7 +2368,7 @@
     PR_LOG(_pr_io_lm, PR_LOG_DEBUG, ("dlopen(0) returns %p", handle));
     close_it = PR_TRUE;
   }
-  pt_solaris_sendfilev_fptr = (ssize_t(*)())dlsym(handle, "sendfilev");
+  pt_solaris_sendfilev_fptr = (ssize_t(*)(int, const struct sendfilevec *, int, size_t *))dlsym(handle, "sendfilev");
   PR_LOG(_pr_io_lm, PR_LOG_DEBUG,
          ("dlsym(sendfilev) returns %p", pt_solaris_sendfilev_fptr));
 
@@ -3104,7 +3104,7 @@
 #  if defined(SOLARIS) || defined(LINUX) ||     \
       defined(__GNU__) || defined(__GLIBC__) || defined(AIX) ||  \
       defined(FREEBSD) || defined(NETBSD) || defined(OPENBSD) || \
-      defined(NTO) || defined(DARWIN) || defined(RISCOS)
+      defined(NTO) || defined(DARWIN) || defined(RISCOS) || defined(IRIX)
 #    define _PR_FCNTL_FLAGS O_NONBLOCK
 #  else
 #    error "Can't determine architecture"
