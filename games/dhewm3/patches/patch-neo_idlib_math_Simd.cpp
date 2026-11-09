$NetBSD$

idSIMD_Revenir: under revenir, the generic SIMD code's hot spots on the
host CPU's SIMD (revenir's syssgi math door); elsewhere not used.

--- neo/idlib/math/Simd.cpp.orig
+++ neo/idlib/math/Simd.cpp
@@ -44,6 +44,7 @@
 #include "idlib/math/Simd_SSE2.h"
 #include "idlib/math/Simd_SSE3.h"
 #include "idlib/math/Simd_AltiVec.h"
+#include "idlib/math/Simd_Revenir.h"
 #include "idlib/math/Plane.h"
 #include "idlib/bv/Bounds.h"
 #include "idlib/Lib.h"
@@ -86,7 +87,10 @@
 	} else {
 
 		if ( !processor ) {
-			if ( ( cpuid & CPUID_ALTIVEC ) ) {
+			// Under revenir: its host's SIMD, through its math door.
+			if ( idSIMD_Revenir::Available() ) {
+				processor = new idSIMD_Revenir;
+			} else if ( ( cpuid & CPUID_ALTIVEC ) ) {
 				processor = new idSIMD_AltiVec;
 			} else if ( ( cpuid & CPUID_MMX ) && ( cpuid & CPUID_SSE ) && ( cpuid & CPUID_SSE2 ) && ( cpuid & CPUID_SSE3 ) ) {
 				processor = new idSIMD_SSE3;
