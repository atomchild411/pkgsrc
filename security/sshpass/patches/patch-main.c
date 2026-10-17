$NetBSD$

Without TIOCSCTTY (IRIX), the session leader takes the terminal by opening it without O_NOCTTY.

--- main.c.orig
+++ main.c
@@ -336,6 +336,7 @@
         setsid();
 
         // Attach the process to a controlling TTY.
+#ifdef TIOCSCTTY
         slavept=open(name, O_RDWR | O_NOCTTY);
         // On some systems, an open(2) is insufficient to set the controlling tty (see the documentation for
         // TIOCSCTTY in tty(4)).
@@ -343,6 +344,10 @@
             perror("sshpass: Failed to set controlling terminal in child (TIOCSCTTY)");
             exit(RETURN_RUNTIME_ERROR);
         }
+#else
+        // No TIOCSCTTY (IRIX): the session leader's open of a terminal makes it the controlling one.
+        slavept=open(name, O_RDWR);
+#endif
         close( slavept ); // We don't need the controlling TTY actually open
 
         close( masterpt );
