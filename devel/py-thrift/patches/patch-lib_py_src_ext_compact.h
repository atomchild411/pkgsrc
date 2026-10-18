$NetBSD$

Big-endian without glibc (IRIX): byte order from the compiler-predefined
__BYTE_ORDER__; htons() from <arpa/inet.h> (IRIX <netinet/in.h> has it
only in SGI mode, Python.h asks for X/Open); letohll/htolell as a real
64-bit swap (ntohl is the identity there); and writeDouble swaps the
double's bits, not its value converted to an integer.

--- lib/py/src/ext/compact.h.orig
+++ lib/py/src/ext/compact.h
@@ -49,7 +49,8 @@
       double f;
       int64_t t;
     } transfer;
-    transfer.f = htolell(dub);
+    transfer.f = dub;
+    transfer.t = htolell(transfer.t);
     writeBuffer(reinterpret_cast<char*>(&transfer.t), sizeof(int64_t));
   }
 
