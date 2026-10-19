$NetBSD$

A cross build cannot run the keysym and libstroke tests: assume current X11 and libstroke. IRIX declares an m_sync().

--- modules/FvwmEvent/FvwmEvent.c.orig
+++ modules/FvwmEvent/FvwmEvent.c
@@ -187,6 +187,8 @@
 static int rplay_fd = -1;
 static unsigned int m_selected = 0;
 static unsigned int mx_selected = 0;
+/* IRIX's <task.h> (via <ulocks.h>) declares an m_sync(): rename this one. */
+#define m_sync fvwmevent_m_sync
 static unsigned int m_sync = 0;
 static unsigned int mx_sync = 0;
 
