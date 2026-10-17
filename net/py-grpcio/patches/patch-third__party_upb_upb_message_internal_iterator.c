$NetBSD$

IRIX 6.5 (GPR_IRIX): as for net/grpc.

--- third_party/upb/upb/message/internal/iterator.c.orig
+++ third_party/upb/upb/message/internal/iterator.c
@@ -24,7 +24,7 @@
                                              const upb_MiniTable* m,
                                              const upb_MiniTableField** out_f,
                                              upb_MessageValue* out_v,
-                                             size_t* iter) {
+                                             uintptr_t* iter) {
   const size_t count = upb_MiniTable_FieldCount(m);
   size_t i = *iter;
 
