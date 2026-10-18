$NetBSD$

IRIX: detect the platform; clang does not find flag_t::operator=(uint8) unqualified here.

--- nall/intrinsics.hpp.orig
+++ nall/intrinsics.hpp
@@ -40,7 +40,7 @@
 #elif defined(__APPLE__)
   #define PLATFORM_MACOSX
   Intrinsics::Platform Intrinsics::platform() { return Intrinsics::Platform::MacOSX; }
-#elif defined(linux) || defined(__linux__) || defined(__sun__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__GNU__) || defined(__HAIKU__) || defined(__sun)
+#elif defined(linux) || defined(__linux__) || defined(__sun__) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__GNU__) || defined(__HAIKU__) || defined(__sun) || defined(__sgi)
   #define PLATFORM_X
   Intrinsics::Platform Intrinsics::platform() { return Intrinsics::Platform::X; }
 #else
