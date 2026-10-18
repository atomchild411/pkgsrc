$NetBSD$

IRIX <math.h> defines ffloor; the big-endian part of byteptr.h needs doomtype.h.

--- src/byteptr.h.orig
+++ src/byteptr.h
@@ -16,6 +16,7 @@
 #endif
 
 #include "endian.h"
+#include "doomtype.h" // FUNCINLINE, ATTRINLINE (the big-endian code below)
 
 #ifndef SRB2_BIG_ENDIAN
 //
