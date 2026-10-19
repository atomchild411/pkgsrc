$NetBSD$

The SGI audio driver: ALport and ALconfig are different pointer types, and it has no AUDIODEVICE.

--- audio/sgi/audiodrv.cpp.orig
+++ audio/sgi/audiodrv.cpp
@@ -12,13 +12,15 @@
 	channels = 0;
 	encoding = 0;
 	precision = 0;
-	audio = (config = NULL);
+	config = NULL; audio = NULL;
 }
 
 bool audioDriver::IsThere()
 {
 	// Check device availability and write permissions.
-	return (access(AUDIODEVICE,W_OK)==0);
+	// The SGI driver never defined AUDIODEVICE; the AL finds the device,
+	// and Open() reports failure.
+	return true;
 }
 
 bool audioDriver::Open(udword inFreq, int inPrecision, int inChannels,
@@ -77,7 +79,7 @@
     {
 		ALcloseport(audio);
 		ALfreeconfig(config);
-		audio = (config = NULL);
+		config = NULL; audio = NULL;
     }
 }
 
