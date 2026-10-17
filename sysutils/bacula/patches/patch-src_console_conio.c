$NetBSD: patch-src_console_conio.c,v 1.4 2019/02/07 11:29:31 markd Exp $

- need termios.h, our term.h does not include it
- t_insert_line and t_delete_line are macros in term.h; undef them
- spell HAVE_TERM_H correctly
IRIX's own termcap prototypes only without ncurses (whose <term.h> declares them).

--- src/console/conio.c.orig
+++ src/console/conio.c
@@ -54,11 +54,12 @@
 
 #ifdef HAVE_CONIO
 
+#include <termios.h>
 #include <curses.h>
 #include <term.h>
 
 #ifdef HAVE_SUN_OS
-#ifndef _TERM_H
+#ifndef HAVE_TERM_H
 extern "C" int tgetent(void *, const char *);
 extern "C" int tgetnum(const char *);
 extern "C" char *tgetstr (const char*, char**);
@@ -66,7 +67,7 @@
 #  may need to be moved to after the #endif
 extern "C" char *tgoto (const char *, int, int);
 #endif
-#elif defined(__sgi)
+#elif defined(__sgi) && !defined(NCURSES_VERSION)
 extern "C" int tgetent(char *, char *);
 extern "C" int tgetnum(char id[2]);
 extern "C" char *tgetstr(char id[2], char **);
@@ -235,7 +236,9 @@
 static char * getprev(void);
 static void putline(char *newl, int newlen);
 static void t_honk_horn(void);
+#undef t_insert_line
 static void t_insert_line(void);
+#undef t_delete_line
 static void t_delete_line(void);
 static void t_clrline(int pos, int width);
 void t_sendl(const char *msg, int len);
