$NetBSD$

IRIX has random and srandom: do not map them to the lrand48 family.

--- include/system.h.orig
+++ include/system.h
@@ -68,7 +68,7 @@
 # endif		/* !BSD */
 #endif
 
-#ifndef	BSD	/* may be System V */
+#if !defined(BSD) && !defined(sgi)	/* may be System V; IRIX has random */
 # define	srandom(n)	srand48((unsigned int)(n))
 # define	random		lrand48
 #endif		/* !BSD */
