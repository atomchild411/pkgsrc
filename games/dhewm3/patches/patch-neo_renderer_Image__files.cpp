$NetBSD$

Read the TGA and BMP headers byte by byte: the 16- and 32-bit fields are
at odd offsets, and *(short *)buf_p is a misaligned load, which real
IRIX ends with SIGBUS (dhewm3 died at start-up on an Octane2).

--- neo/renderer/Image_files.cpp.orig
+++ neo/renderer/Image_files.cpp
@@ -39,6 +39,18 @@
 
 #include "renderer/Image.h"
 
+// Little-endian fields at any alignment (file headers): a cast to short *
+// or int * there is a misaligned load, which strict-alignment CPUs (IRIX
+// on MIPS) end with SIGBUS.
+static short ReadLittleShortUnaligned( const byte *p ) {
+	return (short)( p[0] | ( p[1] << 8 ) );
+}
+
+static int ReadLittleIntUnaligned( const byte *p ) {
+	return (int)( (unsigned int)p[0] | ( (unsigned int)p[1] << 8 ) |
+		( (unsigned int)p[2] << 16 ) | ( (unsigned int)p[3] << 24 ) );
+}
+
 /*
 
 This file only has a single entry point:
@@ -240,33 +252,33 @@
 
 	bmpHeader.id[0] = *buf_p++;
 	bmpHeader.id[1] = *buf_p++;
-	bmpHeader.fileSize = LittleInt( * ( int * ) buf_p );
+	bmpHeader.fileSize = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.reserved0 = LittleInt( * ( int * ) buf_p );
+	bmpHeader.reserved0 = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.bitmapDataOffset = LittleInt( * ( int * ) buf_p );
+	bmpHeader.bitmapDataOffset = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.bitmapHeaderSize = LittleInt( * ( int * ) buf_p );
+	bmpHeader.bitmapHeaderSize = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.width = LittleInt( * ( int * ) buf_p );
+	bmpHeader.width = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.height = LittleInt( * ( int * ) buf_p );
+	bmpHeader.height = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.planes = LittleShort( * ( short * ) buf_p );
+	bmpHeader.planes = ReadLittleShortUnaligned( buf_p );
 	buf_p += 2;
-	bmpHeader.bitsPerPixel = LittleShort( * ( short * ) buf_p );
+	bmpHeader.bitsPerPixel = ReadLittleShortUnaligned( buf_p );
 	buf_p += 2;
-	bmpHeader.compression = LittleInt( * ( int * ) buf_p );
+	bmpHeader.compression = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.bitmapDataSize = LittleInt( * ( int * ) buf_p );
+	bmpHeader.bitmapDataSize = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.hRes = LittleInt( * ( int * ) buf_p );
+	bmpHeader.hRes = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.vRes = LittleInt( * ( int * ) buf_p );
+	bmpHeader.vRes = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.colors = LittleInt( * ( int * ) buf_p );
+	bmpHeader.colors = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
-	bmpHeader.importantColors = LittleInt( * ( int * ) buf_p );
+	bmpHeader.importantColors = ReadLittleIntUnaligned( buf_p );
 	buf_p += 4;
 
 	memcpy( bmpHeader.palette, buf_p, sizeof( bmpHeader.palette ) );
@@ -553,18 +565,18 @@
 	targa_header.colormap_type = *buf_p++;
 	targa_header.image_type = *buf_p++;
 
-	targa_header.colormap_index = LittleShort ( *(short *)buf_p );
+	targa_header.colormap_index = ReadLittleShortUnaligned( buf_p );
 	buf_p += 2;
-	targa_header.colormap_length = LittleShort ( *(short *)buf_p );
+	targa_header.colormap_length = ReadLittleShortUnaligned( buf_p );
 	buf_p += 2;
 	targa_header.colormap_size = *buf_p++;
-	targa_header.x_origin = LittleShort ( *(short *)buf_p );
+	targa_header.x_origin = ReadLittleShortUnaligned( buf_p );
 	buf_p += 2;
-	targa_header.y_origin = LittleShort ( *(short *)buf_p );
+	targa_header.y_origin = ReadLittleShortUnaligned( buf_p );
 	buf_p += 2;
-	targa_header.width = LittleShort ( *(short *)buf_p );
+	targa_header.width = ReadLittleShortUnaligned( buf_p );
 	buf_p += 2;
-	targa_header.height = LittleShort ( *(short *)buf_p );
+	targa_header.height = ReadLittleShortUnaligned( buf_p );
 	buf_p += 2;
 	targa_header.pixel_size = *buf_p++;
 	targa_header.attributes = *buf_p++;
