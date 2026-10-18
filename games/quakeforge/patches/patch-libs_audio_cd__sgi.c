$NetBSD$

Declare I_SGI_Stop before its first use.

--- libs/audio/cd_sgi.c.orig
+++ libs/audio/cd_sgi.c
@@ -45,6 +45,8 @@
 
 #include "compat.h"
 
+void I_SGI_Stop (void);
+
 static plugin_t plugin_info;
 static plugin_data_t plugin_info_data;
 static plugin_funcs_t plugin_info_funcs;
