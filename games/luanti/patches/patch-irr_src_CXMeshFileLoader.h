$NetBSD$

Big-endian hosts byteswap with os::Byteswap (os.h).

--- irr/src/CXMeshFileLoader.h.orig
+++ irr/src/CXMeshFileLoader.h
@@ -9,6 +9,7 @@
 #include "irrString.h"
 #include "S3DVertex.h"
 #include "SkinnedMesh.h"
+#include "os.h"
 
 #include <algorithm>
 #include <cstring>
