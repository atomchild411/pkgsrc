$NetBSD$

setpgrp(pid, pgrp) is BSD's; POSIX (and IRIX, whose setpgrp takes none) has setpgid.

--- batchftp.c.orig
+++ batchftp.c
@@ -803,7 +803,7 @@
 		*mptr = msg_ptr;
 		if (monitor_flag == -1) {     /*ftp producing not output -- kill subprocesses */
 			unlink(f_stdout);
-			pg_flag = setpgrp(pid, pid);                      /* make child group leader so that parent won't be killed */
+			pg_flag = setpgid(pid, pid);                      /* make child group leader so that parent won't be killed */
 			if ((killpg(pid, SIGKILL) != -1) && (pg_flag != -1)) /* kill child and the ftp process initiated by sh script */
 				return;
 			}
