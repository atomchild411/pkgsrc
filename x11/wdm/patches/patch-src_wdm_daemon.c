$NetBSD$

setpgrp(pid, pgrp) is BSD's; POSIX (and IRIX, whose setpgrp takes none) has setpgid.

--- src/wdm/daemon.c.orig
+++ src/wdm/daemon.c
@@ -98,7 +98,7 @@
 #if defined(SYSV)
 	stat = 0;	/* don't know how to set child's process group */
 #else
-	stat = setpgrp(child_id, child_id);
+	stat = setpgid(child_id, child_id);
 	if (stat != 0)
 	    WDMError("setting process grp for daemon failed, errno = %d\n",
 		     errno);
@@ -122,7 +122,7 @@
 #if defined(SYSV) || defined(SVR4) || defined(__QNXNTO__)
     setpgrp ();
 #else
-    setpgrp (0, getpid());
+    setpgid (0, getpid());
 #endif
 
     close (0); 
