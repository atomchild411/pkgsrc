$NetBSD$

IRIX n32: intptr_t is long and ptrdiff_t int; the definitions of the
qore_offset_t methods (QoreListNode::splice, ...) are written with ptrdiff_t.

--- include/qore/common.h.orig
+++ include/qore/common.h
@@ -73,7 +73,12 @@
 typedef size_t qore_size_t;
 
 //! used for offsets that could be negative
+#ifdef __sgi
+// IRIX n32: intptr_t is long and ptrdiff_t int, which the definitions use
+typedef ptrdiff_t qore_offset_t;
+#else
 typedef intptr_t qore_offset_t;
+#endif
 
 //! used for the unique class ID for QoreClass objects
 typedef unsigned qore_classid_t;
