$NetBSD$

Accept OpenGL 1.1 and later (IRIX: SGI's OpenGL 1.2 on VPro, without
GL_SGIS_generate_mipmap). The GL1 renderer uses nothing newer except
GL_GENERATE_MIPMAP for non power of two textures, which are only used
where that is available; otherwise mipmaps are made in software.

--- src/client/refresh/gl1/gl1_main.c.orig
+++ src/client/refresh/gl1/gl1_main.c
@@ -1457,10 +1457,11 @@
 
 	if (gl_config.major_version == 1)
 	{
-		if (gl_config.minor_version < 4)
+		// 1.1 is enough (see gl1_sdl.c).
+		if (gl_config.minor_version < 1)
 		{
 			QGL_Shutdown();
-			R_Printf(PRINT_ALL, "Support for OpenGL 1.4 is not available\n");
+			R_Printf(PRINT_ALL, "Support for OpenGL 1.1 is not available\n");
 
 			return false;
 		}
@@ -1554,7 +1555,11 @@
 	/* Non power of two textures */
 	R_Printf(PRINT_ALL, " - Non power of two textures: ");
 
-	if (strstr(gl_config.extensions_string, "GL_ARB_texture_non_power_of_two"))
+	// The non power of two upload makes mipmaps with GL_GENERATE_MIPMAP:
+	// OpenGL 1.4, or GL_SGIS_generate_mipmap before it.
+	if (strstr(gl_config.extensions_string, "GL_ARB_texture_non_power_of_two") &&
+		(gl_config.major_version > 1 || gl_config.minor_version >= 4 ||
+		 strstr(gl_config.extensions_string, "GL_SGIS_generate_mipmap")))
 	{
 		gl_config.npottextures = true;
 		R_Printf(PRINT_ALL, "Okay\n");
