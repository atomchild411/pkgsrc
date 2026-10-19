$NetBSD$

npy_intp and Py_intptr_t are different types where intptr_t is long and Py_ssize_t int (IRIX n32): cast between them.

--- libs/python/src/numpy/ndarray.cpp.orig
+++ libs/python/src/numpy/ndarray.cpp
@@ -127,8 +127,8 @@
     (PyArray_NewFromDescr(&PyArray_Type,
 			  incref_dtype(dt),
 			  shape.size(),
-			  const_cast<Py_intptr_t*>(&shape.front()),
-			  const_cast<Py_intptr_t*>(&strides.front()),
+			  reinterpret_cast<npy_intp*>(const_cast<Py_intptr_t*>(&shape.front())),
+			  reinterpret_cast<npy_intp*>(const_cast<Py_intptr_t*>(&strides.front())),
 			  data,
 			  flags,
 			  NULL)));
@@ -240,13 +240,13 @@
   boost::scoped_array<Py_intptr_t> dims(new Py_intptr_t[nd]);
   for (int n=0; n<nd; ++n) dims[n] = python::extract<Py_intptr_t>(shape[n]);
   return ndarray(python::detail::new_reference
-                 (PyArray_Zeros(nd, dims.get(), detail::incref_dtype(dt), 0)));
+                 (PyArray_Zeros(nd, reinterpret_cast<npy_intp*>(dims.get()), detail::incref_dtype(dt), 0)));
 }
 
 ndarray zeros(int nd, Py_intptr_t const * shape, dtype const & dt) 
 {
   return ndarray(python::detail::new_reference
-    (PyArray_Zeros(nd, const_cast<Py_intptr_t*>(shape), detail::incref_dtype(dt), 0)));
+    (PyArray_Zeros(nd, reinterpret_cast<npy_intp*>(const_cast<Py_intptr_t*>(shape)), detail::incref_dtype(dt), 0)));
 }
 
 ndarray empty(python::tuple const & shape, dtype const & dt) 
@@ -255,13 +255,13 @@
   boost::scoped_array<Py_intptr_t> dims(new Py_intptr_t[nd]);
   for (int n=0; n<nd; ++n) dims[n] = python::extract<Py_intptr_t>(shape[n]);
   return ndarray(python::detail::new_reference
-                 (PyArray_Empty(nd, dims.get(), detail::incref_dtype(dt), 0)));    
+                 (PyArray_Empty(nd, reinterpret_cast<npy_intp*>(dims.get()), detail::incref_dtype(dt), 0)));    
 }
 
 ndarray empty(int nd, Py_intptr_t const * shape, dtype const & dt)
 {
   return ndarray(python::detail::new_reference
-    (PyArray_Empty(nd, const_cast<Py_intptr_t*>(shape), detail::incref_dtype(dt), 0)));
+    (PyArray_Empty(nd, reinterpret_cast<npy_intp*>(const_cast<Py_intptr_t*>(shape)), detail::incref_dtype(dt), 0)));
 }
 
 ndarray array(python::object const & obj) 
