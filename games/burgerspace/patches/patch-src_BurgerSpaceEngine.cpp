$NetBSD$

std::stringstream needs <sstream> (libc++ does not bring it with <fstream>).

--- src/BurgerSpaceEngine.cpp.orig
+++ src/BurgerSpaceEngine.cpp
@@ -28,6 +28,7 @@
 
 #include <assert.h>
 #include <fstream>
+#include <sstream>
 #include <iomanip>
 #include <algorithm>
 
