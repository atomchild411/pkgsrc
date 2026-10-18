$NetBSD$

IRIX: System V's setpgrp(), though it has TIOCNOTTY.

--- daemon.c.orig
+++ daemon.c
@@ -247,7 +247,7 @@
        * and process group; ensure the process can't reaquire a 
        * controlling terminal
        */
-#if defined TIOCNOTTY && !defined __linux__     /* BSD */
+#if defined TIOCNOTTY && !defined __linux__ && !defined __sgi    /* BSD */
       if (setpgrp (0, getpid ()) == -1)
         exit_proxy (EXIT_NORMAL);
 
