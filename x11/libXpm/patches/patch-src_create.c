$NetBSD$

Choose the 16- and 32-bit pixel writers by the image byte order, not the
bitmap bit order. A server with LSB byte order and MSB bit order (a
big-endian IRIX client on Xwayland) got MSB pixels in an LSB image:
the blue channel was lost and grey and white came out yellow.

--- src/create.c.orig
+++ src/create.c
@@ -1984,7 +1984,7 @@
 	    else
 		ximage->f.put_pixel = PutPixel1LSB;
 	else if (ximage->bits_per_pixel == 16)
-	    if (ximage->bitmap_bit_order == MSBFirst)
+	    if (ximage->byte_order == MSBFirst)
 		ximage->f.put_pixel = PutPixel16MSB;
 	    else
 		ximage->f.put_pixel = PutPixel16LSB;
@@ -1994,7 +1994,7 @@
 		ximage->f.put_pixel = PutPixel32;
 	    else
 #endif
-		if (ximage->bitmap_bit_order == MSBFirst)
+		if (ximage->byte_order == MSBFirst)
 		    ximage->f.put_pixel = PutPixel32MSB;
 		else
 		    ximage->f.put_pixel = PutPixel32LSB;
