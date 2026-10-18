$NetBSD$

setpgrp(pid, pgrp) is BSD's; POSIX (and IRIX, whose setpgrp takes none) has setpgid.

--- src/smmain.c.orig
+++ src/smmain.c
@@ -1114,7 +1114,7 @@
 		#if defined(__linux__) || defined(__svr4__)
 		setpgid(fpid,fpid);
 		#else
-		setpgrp(fpid,fpid);
+		setpgid(fpid,fpid);
 		#endif /* __linux__ || __svr4__ */
 		
 		setuid(geteuid());
@@ -1169,7 +1169,7 @@
 		#if defined(__linux__) || defined(__svr4__)
 		setpgid(fpid,fpid);
 		#else
-		setpgrp(fpid,fpid);
+		setpgid(fpid,fpid);
 		#endif /* __linux__ || __svr4__ */
 				
 		if(execvp("sh",argv) == (-1)) errval = errno;
