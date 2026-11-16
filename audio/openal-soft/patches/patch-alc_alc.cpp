$NetBSD$

The IRIX Audio Library backend.

--- alc/alc.cpp.orig
+++ alc/alc.cpp
@@ -144,6 +144,9 @@
 #endif
 #if HAVE_OSS
 #include "backends/oss.h"
+#endif
+#if HAVE_IRIXAL
+#include "backends/irixal.h"
 #endif
 #if HAVE_DSOUND
 #include "backends/dsound.h"
@@ -256,6 +259,9 @@
 #if HAVE_SOLARIS
     BackendInfo{"solaris"sv, SolarisBackendFactory::getFactory},
 #endif
+#if HAVE_IRIXAL
+    BackendInfo{"irixal"sv, IrixALBackendFactory::getFactory},
+#endif
 #if HAVE_SNDIO
     BackendInfo{"sndio"sv, SndIOBackendFactory::getFactory},
 #endif
