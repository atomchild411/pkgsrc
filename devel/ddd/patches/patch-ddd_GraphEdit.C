$NetBSD$

Only SGI's own Motif has _SG_vendorExtension, not pkgsrc's.

--- ddd/GraphEdit.C.orig
+++ ddd/GraphEdit.C
@@ -426,7 +426,7 @@
     /* syn_resources            */ (XmSyntheticResource *)0,
     /* num_syn_resources        */ 0,
     /* extension                */ XtPointer(0)
-#if defined(__sgi) && !defined(LesstifVersion)
+#if defined(__sgi) && !defined(LesstifVersion) && !defined(NO_SG_VENDOR_EXTENSION)
 	// Paul Sydney <sydney@ulua.mhpcc.af.mil> reports that OSF/Motif
 	// on an SGI Indy running IRIX 6.5 has an extra
 	// `_SG_vendorExtension' field.  If this is not initialized
