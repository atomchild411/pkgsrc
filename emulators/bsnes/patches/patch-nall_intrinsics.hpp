$NetBSD: patch-nall_intrinsics.hpp,v 1.1 2020/10/20 12:21:19 nia Exp $

Use standard bits from endian.h.

Fixes building on NetBSD/aarch64.
IRIX: use the Linux (plain POSIX, endian.h) platform branch.

--- nall/intrinsics.hpp.orig
+++ nall/intrinsics.hpp
@@ -91,7 +91,7 @@
   constexpr auto platform() -> Platform { return Platform::Android; }
   constexpr auto api() -> API { return API::Posix; }
   constexpr auto display() -> DisplayServer { return DisplayServer::Unknown; }
-#elif defined(linux) || defined(__linux__)
+#elif defined(linux) || defined(__linux__) || defined(__sgi)
   #define PLATFORM_LINUX
   #define API_POSIX
   #define DISPLAY_XORG
@@ -159,10 +159,14 @@
 
 namespace nall {
 
-#if (defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN) || defined(__LITTLE_ENDIAN__) || defined(__i386__) || defined(__amd64__) || defined(_M_IX86) || defined(_M_AMD64)
+#if (defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN) || \
+    (defined(BYTE_ORDER) && defined(LITTLE_ENDIAN) && BYTE_ORDER == LITTLE_ENDIAN) || \
+    defined(__LITTLE_ENDIAN__) || defined(__i386__) || defined(__amd64__) || defined(_M_IX86) || defined(_M_AMD64)
   #define ENDIAN_LSB
   constexpr auto endian() -> Endian { return Endian::LSB; }
-#elif (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN) || defined(__BIG_ENDIAN__) || defined(__powerpc__) || defined(_M_PPC)
+#elif (defined(__BYTE_ORDER) && defined(__BIG_ENDIAN) && __BYTE_ORDER == __BIG_ENDIAN) || \
+    (defined(BYTE_ORDER) && defined(BIG_ENDIAN) && BYTE_ORDER == BIG_ENDIAN) || \
+    defined(__BIG_ENDIAN__) || defined(__powerpc__) || defined(_M_PPC)
   #define ENDIAN_MSB
   constexpr auto endian() -> Endian { return Endian::MSB; }
 #else
