$NetBSD: patch-update.c,v 1.2 2018/12/18 14:16:18 hauke Exp $

Newer Linuxen (2018 Arch here) have moved makedev(3) and friends
from <sys/types.h> to <sys/sysmacros.h>

Fix for Radmind bug #221, accomodating for 64 bit time_t
IRIX, like Solaris, has makedev in <sys/mkdev.h>.

--- update.c.orig
+++ update.c
@@ -6,9 +6,12 @@
 #include "config.h"
 
 #include <sys/types.h>
+#if defined (__linux__)
+#include <sys/sysmacros.h>
+#endif
 #include <sys/stat.h>
 #include <sys/param.h>
-#ifdef sun
+#if defined(sun) || defined(__sgi)
 #include <sys/mkdev.h>
 #endif /* sun */
 #ifdef __APPLE__
@@ -26,6 +29,7 @@
 #include "update.h"
 #include "code.h"
 #include "radstat.h"
+#include "largefile.h"
 #include "transcript.h"
 #include "progress.h"
 #include "mkdirs.h"
@@ -73,7 +77,7 @@
 
 	mode = strtol( targv[ 2 ], (char **)NULL, 8 );
 
-	times.modtime = atoi( targv[ 5 ] );
+	times.modtime = strtotimet( targv[ 5 ], NULL, 10 );
 	if ( times.modtime != st->st_mtime ) {
 	    times.actime = st->st_atime;
 	    if ( utime( path, &times ) != 0 ) {
