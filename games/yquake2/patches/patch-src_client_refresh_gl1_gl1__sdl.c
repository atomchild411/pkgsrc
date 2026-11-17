$NetBSD$

Accept OpenGL 1.1 and later (IRIX: SGI's OpenGL 1.2 on VPro, without
GL_SGIS_generate_mipmap). The GL1 renderer uses nothing newer except
GL_GENERATE_MIPMAP for non power of two textures, which are only used
where that is available; otherwise mipmaps are made in software.

--- src/client/refresh/gl1/gl1_sdl.c.orig
+++ src/client/refresh/gl1/gl1_sdl.c
@@ -206,9 +206,13 @@
 	const char* glver = (char *)glGetString(GL_VERSION);
 	sscanf(glver, "%d.%d", &gl_config.major_version, &gl_config.minor_version);
 
-	if (gl_config.major_version < 1 || (gl_config.major_version == 1 && gl_config.minor_version < 4))
+	// What the GL1 renderer needs is OpenGL 1.1 (texture objects, vertex
+	// arrays). GL_GENERATE_MIPMAP (1.4) only goes with non power of two
+	// textures, which gl1_main.c turns on only where it is there; otherwise
+	// mipmaps are made in software (IRIX: SGI's OpenGL 1.2 on VPro).
+	if (gl_config.major_version < 1 || (gl_config.major_version == 1 && gl_config.minor_version < 1))
 	{
-		R_Printf(PRINT_ALL, "R_InitContext(): Got an OpenGL version %d.%d context - need (at least) 1.4!\n", gl_config.major_version, gl_config.minor_version);
+		R_Printf(PRINT_ALL, "R_InitContext(): Got an OpenGL version %d.%d context - need (at least) 1.1!\n", gl_config.major_version, gl_config.minor_version);
 
 		return false;
 	}
