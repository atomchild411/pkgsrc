$NetBSD$

IRIX <nl_types.h> defines MALLOC.

--- src/tools/tArray.h.orig
+++ src/tools/tArray.h
@@ -69,6 +69,9 @@
 };
 
 
+// IRIX's <nl_types.h> defines MALLOC (a catalog type).
+#undef MALLOC
+
 template<class T, bool MALLOC=false> class tArray: public GrowingArrayBase {
 protected:
     void Init(){
