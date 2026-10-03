$NetBSD$

The definition takes size_t *, the declaration in iterator.h uintptr_t *:
conflicting types wherever the two differ (IRIX n32: unsigned int and
unsigned long).

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
 
