$NetBSD$

fcntl() is declared in <fcntl.h> (IRIX's <sys/fcntl.h> has none).

--- native/jni/java-nio/javanio.c.orig
+++ native/jni/java-nio/javanio.c
@@ -42,7 +42,7 @@
  */
 
 #include <sys/types.h>
-#include <sys/fcntl.h>
+#include <fcntl.h>	/* fcntl(); IRIX's <sys/fcntl.h> declares none */
 #include <sys/socket.h>
 #include <sys/uio.h>
 #include <unistd.h>
