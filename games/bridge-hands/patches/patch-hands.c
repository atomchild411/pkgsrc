$NetBSD$

IRIX: <stdio.h> declares getopt (with const).

--- hands.c.orig
+++ hands.c
@@ -49,7 +49,9 @@
 void print_page(int starting_hand);
 void bprint(char *out,char *in);
 void print_usage(void);
+#ifndef __sgi	/* IRIX: <stdio.h> declares getopt */
 int getopt(int, char **, char *);
+#endif
 long atol(char *);
 time_t time(time_t *);
 void exit(int);
