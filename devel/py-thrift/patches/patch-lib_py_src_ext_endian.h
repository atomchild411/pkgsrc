$NetBSD$

Big-endian without glibc (IRIX): byte order from the compiler-predefined
__BYTE_ORDER__; htons() from <arpa/inet.h> (IRIX <netinet/in.h> has it
only in SGI mode, Python.h asks for X/Open); letohll/htolell as a real
64-bit swap (ntohl is the identity there); and writeDouble swaps the
double's bits, not its value converted to an integer.

--- lib/py/src/ext/endian.h.orig
+++ lib/py/src/ext/endian.h
@@ -24,6 +24,7 @@
 
 #ifndef _WIN32
 #include <netinet/in.h>
+#include <arpa/inet.h>
 #else
 #include <winsock2.h>
 #pragma comment(lib, "ws2_32.lib")
@@ -57,6 +58,10 @@
 #define __BYTE_ORDER BYTE_ORDER
 #define __LITTLE_ENDIAN LITTLE_ENDIAN
 #define __BIG_ENDIAN BIG_ENDIAN
+#elif defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && defined(__ORDER_BIG_ENDIAN__)
+#define __BYTE_ORDER __BYTE_ORDER__
+#define __LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
+#define __BIG_ENDIAN __ORDER_BIG_ENDIAN__
 #else
 #error "Cannot determine endianness"
 #endif
@@ -70,6 +75,9 @@
 #include <byteswap.h>
 #define letohll(n) bswap_64(n)
 #define htolell(n) bswap_64(n)
+#elif defined(__GNUC__)
+#define letohll(n) __builtin_bswap64(n)
+#define htolell(n) __builtin_bswap64(n)
 #else /* GNUC & GLIBC */
 #define letohll(n) ((((unsigned long long)ntohl(n)) << 32) + ntohl(n >> 32))
 #define htolell(n) ((((unsigned long long)htonl(n)) << 32) + htonl(n >> 32))
