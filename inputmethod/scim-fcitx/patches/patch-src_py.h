$NetBSD$

IRIX: <sys/param.h> defines HZ.

--- src/py.h.orig
+++ src/py.h
@@ -36,6 +36,9 @@
     PY_CAND_LEGEND
 } PY_CAND_WORD_TYPE;
 
+#ifdef HZ	/* IRIX <sys/param.h>: clock ticks per second */
+#undef HZ
+#endif
 typedef struct _HZ {
     char            strHZ[MAX_PY_PHRASE_LENGTH * 2 + 1];
     int             iPYFA;
