$NetBSD$

Build comp_err also in a cross build that has an emulator to run it
(CMAKE_CROSSCOMPILING_EMULATOR, the IRIX irix-exec bridge).
IRIX has neither ppoll nor kqueue: poll() in vio, as on Windows.
The bundled boost's MIPSpro workaround is not for clang, which defines
_COMPILER_VERSION on IRIX too.

--- boost/boost_1_77_0/boost/type_index/stl_type_index.hpp.orig
+++ boost/boost_1_77_0/boost/type_index/stl_type_index.hpp
@@ -48,7 +48,7 @@
 #endif
 
 #if (defined(__EDG_VERSION__) && __EDG_VERSION__ < 245) \
-        || (defined(__sgi) && defined(_COMPILER_VERSION) && _COMPILER_VERSION <= 744)
+        || (defined(__sgi) && defined(_COMPILER_VERSION) && _COMPILER_VERSION <= 744 && !defined(__clang__))
 #   include <boost/type_traits/is_signed.hpp>
 #   include <boost/type_traits/make_signed.hpp>
 #   include <boost/type_traits/type_identity.hpp>
@@ -228,7 +228,7 @@
     typedef BOOST_DEDUCED_TYPENAME boost::remove_cv<no_ref_t>::type no_cvr_prefinal_t;
 
     #  if (defined(__EDG_VERSION__) && __EDG_VERSION__ < 245) \
-        || (defined(__sgi) && defined(_COMPILER_VERSION) && _COMPILER_VERSION <= 744)
+        || (defined(__sgi) && defined(_COMPILER_VERSION) && _COMPILER_VERSION <= 744 && !defined(__clang__))
 
         // Old EDG-based compilers seem to mistakenly distinguish 'integral' from 'signed integral'
         // in typeid() expressions. Full template specialization for 'integral' fixes that issue:
