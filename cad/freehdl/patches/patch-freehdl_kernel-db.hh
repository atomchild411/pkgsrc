$NetBSD: patch-freehdl_kernel-db.hh,v 1.1 2013/04/30 22:13:57 joerg Exp $
db_generic_explorer has no get_key of its own: use its internal explorer's.

--- freehdl/kernel-db.hh.orig
+++ freehdl/kernel-db.hh
@@ -254,10 +254,10 @@
 
 // A hash function template used tp generate a hash number from
 // d
-class db_basic_key_hash : public hash<unsigned long> {
+class db_basic_key_hash : public __gnu_cxx::hash<unsigned long> {
 public:
   size_t operator()(const db_basic_key& x) const {
-    return (*(hash<unsigned long> *)this)(((unsigned long)x.value)>>2);
+    return (*(__gnu_cxx::hash<unsigned long> *)this)(((unsigned long)x.value)>>2);
   }
 };
 
@@ -595,7 +595,7 @@
     return *d;
   }
 
-  typename kind::data_type &get (db_basic_key key) { return get (this->get_key (key)); }
+  typename kind::data_type &get (db_basic_key key) { return get (internal_explorer.get_key (key)); }
 };
 
 
