$NetBSD$

IRIX has no TIOCSCTTY: opening the terminal after setsid() made it the
controlling one.

--- src/shell.cpp.orig
+++ src/shell.cpp
@@ -109,7 +109,9 @@
 		close( slaveFd );
 
 		//сделать терминал - контролирующим терминалом
+#ifdef TIOCSCTTY /* else (IRIX) opening it after setsid() made it ours */
 		if ( ioctl( 0, TIOCSCTTY, 0 ) ) { printf( "ioctl(0, TIOCSCTTY, 0) error\n" ); }
+#endif
 
 		ShellProc( pipe2[0], pipe1[1] );
 		exit( 1 );
