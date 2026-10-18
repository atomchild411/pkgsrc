$NetBSD$

IRIX <unistd.h> defines EX_OK.

--- src/util/exitcode.h.orig
+++ src/util/exitcode.h
@@ -3,6 +3,7 @@
 
 // Semantic exit codes, as defined by BSD sysexits(3)
 enum {
+#undef EX_OK // IRIX's <unistd.h> has one (an access() mode)
     EX_OK = 0, // Exited normally
     EX_USAGE = 64, // Command line usage error
     EX_DATAERR = 65, // Input data error
