$NetBSD$

Accept OpenGL 1.2 with GL_SGIS_generate_mipmap (IRIX): GL_GENERATE_MIPMAP
is the only OpenGL 1.4 feature the GL1 renderer uses.

--- src/client/refresh/gl1/gl1_sdl.c.orig
+++ src/client/refresh/gl1/gl1_sdl.c
@@ -206,7 +206,13 @@
 	const char* glver = (char *)glGetString(GL_VERSION);
 	sscanf(glver, "%d.%d", &gl_config.major_version, &gl_config.minor_version);
 
-	if (gl_config.major_version < 1 || (gl_config.major_version == 1 && gl_config.minor_version < 4))
+	// 1.4's only feature used here is GL_GENERATE_MIPMAP, which
+	// GL_SGIS_generate_mipmap gives older versions (IRIX: 1.2).
+	const char* glext = (char *)glGetString(GL_EXTENSIONS);
+	qboolean genmip = glext != NULL && strstr(glext, "GL_SGIS_generate_mipmap") != NULL;
+
+	if (gl_config.major_version < 1 || (gl_config.major_version == 1 && gl_config.minor_version < 4 &&
+		!(gl_config.minor_version >= 2 && genmip)))
 	{
 		R_Printf(PRINT_ALL, "R_InitContext(): Got an OpenGL version %d.%d context - need (at least) 1.4!\n", gl_config.major_version, gl_config.minor_version);
 
