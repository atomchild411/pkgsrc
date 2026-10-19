$NetBSD$

dlopen() is used whether or not RTLD_NOLOAD exists (IRIX has none): always include <dlfcn.h>.

--- ext/soup/gstsouploader.c.orig
+++ ext/soup/gstsouploader.c
@@ -19,9 +19,7 @@
 #include "gstsouploader.h"
 #include <gmodule.h>
 
-#ifdef HAVE_RTLD_NOLOAD
 #include <dlfcn.h>
-#endif
 
 #ifdef BUILDING_ADAPTIVEDEMUX2
 GST_DEBUG_CATEGORY (gst_adaptivedemux_soup_debug);
