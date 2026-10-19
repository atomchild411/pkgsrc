$NetBSD$

npy_intp and Py_intptr_t are different types where intptr_t is long and Py_ssize_t int (IRIX n32): cast between them.

--- libs/python/src/numpy/ufunc.cpp.orig
+++ libs/python/src/numpy/ufunc.cpp
@@ -54,7 +54,7 @@
 
 Py_intptr_t const * multi_iter::get_shape() const 
 {
-  return reinterpret_cast<PyArrayMultiIterObject*>(ptr())->dimensions;
+  return reinterpret_cast<Py_intptr_t const *>(reinterpret_cast<PyArrayMultiIterObject*>(ptr())->dimensions);
 }
 
 Py_intptr_t multi_iter::shape(int n) const
