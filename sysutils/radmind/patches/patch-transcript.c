$NetBSD: patch-transcript.c,v 1.2 2018/12/18 14:16:18 hauke Exp $

Newer Linuxen (2018 Arch here) have moved makedev(3) and friends
from <sys/types.h> to <sys/sysmacros.h>

Fix for Radmind bug #221, accomodating for 64 bit time_t
IRIX, like Solaris, has makedev in <sys/mkdev.h>.

--- transcript.c.orig
+++ transcript.c
@@ -6,8 +6,11 @@
 #include "config.h"
 
 #include <sys/types.h>
+#if defined (__linux__)
+#include <sys/sysmacros.h>
+#endif
 #include <sys/param.h>
-#ifdef sun
+#if defined(sun) || defined(__sgi)
 #include <sys/mkdev.h>
 #endif /* sun */
 #include <errno.h>
@@ -271,7 +274,7 @@
 	tran->t_pinfo.pi_stat.st_mode = strtol( argv[ 2 ], NULL, 8 );
 	tran->t_pinfo.pi_stat.st_uid = atoi( argv[ 3 ] );
 	tran->t_pinfo.pi_stat.st_gid = atoi( argv[ 4 ] );
-	tran->t_pinfo.pi_stat.st_mtime = atoi( argv[ 5 ] );
+	tran->t_pinfo.pi_stat.st_mtime = strtotimet( argv[ 5 ], NULL, 10 );
 	tran->t_pinfo.pi_stat.st_size = strtoofft( argv[ 6 ], NULL, 10 );
 	if ( tran->t_type != T_NEGATIVE ) {
 	    if (( cksum ) && ( strcmp( "-", argv [ 7 ] ) == 0  )) {
@@ -436,12 +439,13 @@
 	 * but the corresponding transcript is negative, hence, retain
 	 * the file system's mtime.  Woof!
 	 */
-	fprintf( outtran, "%c %-37s\t%.4lo %5d %5d %9d %7" PRIofft "d %s\n",
+	fprintf( outtran, "%c %-37s\t%.4lo %5d %5d %9" PRItimet "d "
+			  "%7" PRIofft "d %s\n",
 		cur->pi_type, epath,
 		(unsigned long)( T_MODE & cur->pi_stat.st_mode ), 
 		(int)cur->pi_stat.st_uid, (int)cur->pi_stat.st_gid,
 		( flag == PR_STATUS_NEG ) ?
-			(int)fs->pi_stat.st_mtime : (int)cur->pi_stat.st_mtime,
+			fs->pi_stat.st_mtime : cur->pi_stat.st_mtime,
 		cur->pi_stat.st_size, cur->pi_cksum_b64 );
 	break;
 
