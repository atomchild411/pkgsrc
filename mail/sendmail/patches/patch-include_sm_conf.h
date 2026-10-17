$NetBSD$

IRIX 5 and 6 have POSIX setpgid (the BSDsetpgrp rename is for IRIX 4);
IRIX has no res_ninit (NAMED_RESN 0).

--- include/sm/conf.h.orig
+++ include/sm/conf.h
@@ -302,7 +302,10 @@
 #  define HASFCHMOD	1	/* has fchmod(2) syscall */
 #  define HASGETUSERSHELL 0	/* does not have getusershell(3) call */
 #  define IP_SRCROUTE	1	/* can check IP source routing */
-#  define setpgid	BSDsetpgrp
+#  if !defined(IRIX5) && !defined(IRIX6) && !defined(IRIX64)
+#   define setpgid	BSDsetpgrp	/* IRIX 5 and 6 have POSIX setpgid */
+#  endif
+#  define NAMED_RESN	0	/* no res_ninit and friends */
 #  define GIDSET_T	gid_t
 #  define SFS_TYPE	SFS_4ARGS	/* four argument statfs() call */
 #  define SFS_BAVAIL	f_bfree		/* alternate field name */
