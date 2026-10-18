$NetBSD$

IRIX: detect the platform; clang does not find flag_t::operator=(uint8) unqualified here.

--- processor/r65816/registers.hpp.orig
+++ processor/r65816/registers.hpp
@@ -12,9 +12,9 @@
     return data;
   }
 
-  inline unsigned operator|=(unsigned data) { return operator=(operator unsigned() | data); }
-  inline unsigned operator^=(unsigned data) { return operator=(operator unsigned() ^ data); }
-  inline unsigned operator&=(unsigned data) { return operator=(operator unsigned() & data); }
+  inline unsigned operator|=(unsigned data) { return this->operator=(operator unsigned() | data); }
+  inline unsigned operator^=(unsigned data) { return this->operator=(operator unsigned() ^ data); }
+  inline unsigned operator&=(unsigned data) { return this->operator=(operator unsigned() & data); }
 
   flag_t() : n(0), v(0), m(0), x(0), d(0), i(0), z(0), c(0) {}
 };
