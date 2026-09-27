$NetBSD$

IRIX: do not query the terminal (xwsh/old xterm answers end up as stray
text in the pane); mark the replies as received, and still mark the
terminal started -- without TTY_STARTED tmux never writes to it.

--- tty.c.orig
+++ tty.c
@@ -373,12 +373,28 @@
 	if (tty_term_has(tty->term, TTYC_ENBP))
 		tty_putcode(tty, TTYC_ENBP);
 
+#ifdef __sgi
+	/* Don't interrogate the terminal on IRIX. tmux asks any terminal whose
+	 * clear capability starts with ESC[ -- which is every terminal here --
+	 * for its device attributes and foreground/background colours. The
+	 * terminals this system actually has are xwsh and an X11R6-era xterm:
+	 * neither answers the OSC colour queries, and xterm's device-attributes
+	 * reply ("\033[?1;2c") ends up echoed into the pane as stray "1;2c" at
+	 * the shell prompt. Nothing is lost by not asking -- the answers would
+	 * only enable true colour, synchronised updates and similar things that
+	 * an 8-colour 1990s terminal does not have. Mark every reply as already
+	 * received so tmux stops waiting for them. The rest of this function
+	 * must still run: without TTY_STARTED nothing is ever written. */
+	tty->flags |= TTY_ALL_REQUEST_FLAGS;
+	tty->last_requests = time(NULL);
+#else
 	if (tty->term->flags & TERM_VT100LIKE) {
 		/* Subscribe to theme changes and request theme now. */
 		tty_puts(tty, "\033[?2031h\033[?996n");
 	}
 
 	tty_start_start_timer(tty);
+#endif
 
 	tty->flags |= TTY_STARTED;
 	tty_invalidate(tty);
