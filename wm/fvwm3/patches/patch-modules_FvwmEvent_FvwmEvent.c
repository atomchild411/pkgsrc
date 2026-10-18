$NetBSD$

IRIX's <task.h> declares m_sync().

--- modules/FvwmEvent/FvwmEvent.c.orig
+++ modules/FvwmEvent/FvwmEvent.c
@@ -178,7 +178,7 @@
 
 static unsigned int m_selected = 0;
 static unsigned int mx_selected = 0;
-static unsigned int m_sync = 0;
+static unsigned int m_sync_mask = 0;
 static unsigned int mx_sync = 0;
 
 
@@ -196,7 +196,7 @@
 	}
 	else
 	{
-		mask = m_sync;
+		mask = m_sync_mask;
 	}
 	if (evtype & mask)
 	{
@@ -286,14 +286,14 @@
 	/* tell fvwm we're running */
 	SetMessageMask(fd, m_selected);
 	SetMessageMask(fd, mx_selected | M_EXTENDED_MSG);
-	m_sync = (m_selected & SYNC_MASK_M);
+	m_sync_mask = (m_selected & SYNC_MASK_M);
 	mx_sync = (mx_selected & SYNC_MASK_M) | M_EXTENDED_MSG;
 	/* migo (19-Aug-2000): synchronize on M_DESTROY_WINDOW
 	 * dv (6-Jul-2002: synchronize on a number of events that can hide or
 	 * destroy a window */
-	if (m_sync)
+	if (m_sync_mask)
 	{
-		SetSyncMask(fd, m_sync);
+		SetSyncMask(fd, m_sync_mask);
 	}
 	if (mx_sync != M_EXTENDED_MSG)
 	{
