$NetBSD$

On big-endian CPUs, swap the 16-bit .wav samples to the CPU byte order that
OpenAL expects. The SDL mixer path already does this with LittleShort().

--- src/client/sound/openal.c.orig
+++ src/client/sound/openal.c
@@ -198,7 +198,34 @@
 
 	qalGetError();
 	qalGenBuffers(1, &name);
-	qalBufferData(name, format, data, size, s_info->rate);
+
+	if ((s_info->width == 2) && (LittleShort(1) != 1))
+	{
+		/* .wav samples are little-endian; OpenAL wants the CPU's byte order */
+		short *swapped = malloc(size);
+		const byte *src = data;
+		int i;
+
+		if (!swapped)
+		{
+			qalDeleteBuffers(1, &name);
+			return NULL;
+		}
+
+		for (i = 0; i < size / 2; i++)
+		{
+			/* byte-wise: the sample data need not be 2-byte aligned */
+			swapped[i] = (short)(src[2 * i] | (src[2 * i + 1] << 8));
+		}
+
+		qalBufferData(name, format, swapped, size, s_info->rate);
+		free(swapped);
+	}
+	else
+	{
+		qalBufferData(name, format, data, size, s_info->rate);
+	}
+
 	active_buffers++;
 
 	if (qalGetError() != AL_NO_ERROR)
