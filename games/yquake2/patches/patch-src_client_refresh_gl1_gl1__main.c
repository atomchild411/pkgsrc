$NetBSD$

Accept OpenGL 1.2 with GL_SGIS_generate_mipmap (IRIX): GL_GENERATE_MIPMAP
is the only OpenGL 1.4 feature the GL1 renderer uses.

--- src/client/refresh/gl1/gl1_main.c.orig
+++ src/client/refresh/gl1/gl1_main.c
@@ -1457,7 +1457,10 @@
 
 	if (gl_config.major_version == 1)
 	{
-		if (gl_config.minor_version < 4)
+		// Or 1.2 with GL_SGIS_generate_mipmap (gl1_sdl.c).
+		if (gl_config.minor_version < 4 && !(gl_config.minor_version >= 2 &&
+			gl_config.extensions_string != NULL &&
+			strstr(gl_config.extensions_string, "GL_SGIS_generate_mipmap") != NULL))
 		{
 			QGL_Shutdown();
 			R_Printf(PRINT_ALL, "Support for OpenGL 1.4 is not available\n");
