$NetBSD: patch-tcptrace.h,v 1.1 2025/12/13 16:42:03 vins Exp $

IRIX has no struct ether_addr: declare it at file scope (only pointers are used).

--- tcptrace.h.orig
+++ tcptrace.h
@@ -773,6 +773,7 @@
 /* note that many machines have an ether_ntoa, but the output differs, as does
    the prototype, so we'll include our own and change the name to avoid conflicts
    with local prototypes if they exist and differ */
+struct ether_addr;	/* IRIX has none: only used through pointers */
 char *Ether_Ntoa(struct ether_addr *e);
 
 /* global routine decls */
@@ -1115,7 +1116,7 @@
 /* I've had problems with the memcpy function that gcc stuffs into the program
    and alignment problems.  This should fix it! */
 void *MemCpy(void *p1, void *p2, size_t n); /* in tcptrace.c */
-#define memcpy(p1,p2,n) MemCpy(p1,p2,n)
+#define _memcpy(p1,p2,n) MemCpy(p1,p2,n)
 #endif /* __VMS */
 
 #ifdef __VMS
