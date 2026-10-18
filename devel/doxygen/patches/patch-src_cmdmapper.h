$NetBSD$

IRIX: System V filesystem; its <nl_types.h> defines CMD_QUOTE.

--- src/cmdmapper.h.orig
+++ src/cmdmapper.h
@@ -21,6 +21,9 @@
 #include <memory>
 #include "dstring.h"
 
+// IRIX's <nl_types.h> (through <locale>) defines a CMD_QUOTE macro.
+#undef CMD_QUOTE
+
 template<typename T>
 using CommandMap = std::unordered_map< std::string, T >;
 
