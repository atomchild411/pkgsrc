$NetBSD$

Take the byte order from the compiler where it says: build.sh runs a test
program for it, which got little-endian in a cross build for big-endian
IRIX, and the WAV reader then rejected every sound ("not a wave file").

--- src/endian_uqm.h.orig
+++ src/endian_uqm.h
@@ -25,7 +25,14 @@
 #include "config.h"
 #include "types.h"
 
-#if defined (__APPLE__) && defined (__GNUC__)
+#if defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
+// The compiler knows the target's byte order. build.sh finds it by
+// running a test program, which a cross build cannot do reliably.
+#	undef WORDS_BIGENDIAN
+#	if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
+#		define WORDS_BIGENDIAN
+#	endif
+#elif defined (__APPLE__) && defined (__GNUC__)
 // When using the MacOS gcc compiler to build universal binaries,
 // each file will be compiled once for each platform.
 // This means that checking endianness beforehand from build.sh will not do,
