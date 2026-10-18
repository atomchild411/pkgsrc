$NetBSD$

Only SGI's own Motif has _SG_vendorExtension, not pkgsrc's.

--- ddd/LabelH.C.orig
+++ ddd/LabelH.C
@@ -141,7 +141,7 @@
 	0,			      // syn_resources
 	0,                            // num_syn_resources
 	0                             // extension
-#if defined(__sgi) && !defined(LesstifVersion)
+#if defined(__sgi) && !defined(LesstifVersion) && !defined(NO_SG_VENDOR_EXTENSION)
 	// Paul Sydney <sydney@ulua.mhpcc.af.mil> reports that OSF/Motif
 	// on an SGI Indy running IRIX 6.5 has an extra
 	// `_SG_vendorExtension' field.  If this is not initialized
@@ -154,7 +154,7 @@
 	XmInheritMenuProc,            // menuProcs
 	XtInheritTranslations,        // translations
 	0                             // extension
-#if defined(__sgi) && !defined(LesstifVersion)
+#if defined(__sgi) && !defined(LesstifVersion) && !defined(NO_SG_VENDOR_EXTENSION)
 	, 0
 #endif
     },
