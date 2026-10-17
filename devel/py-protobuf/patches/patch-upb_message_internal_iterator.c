$NetBSD$

Define _upb_Message_NextBaseField with the uintptr_t* its declaration has
(size_t is not uintptr_t on ILP32 IRIX: unsigned int vs unsigned long).

--- upb/message/internal/iterator.c.orig
+++ upb/message/internal/iterator.c
@@ -24,7 +24,7 @@
                                              const upb_MiniTable* m,
                                              const upb_MiniTableField** out_f,
                                              upb_MessageValue* out_v,
-                                             size_t* iter) {
+                                             uintptr_t* iter) {
   const size_t count = upb_MiniTable_FieldCount(m);
   size_t i = *iter;
 
