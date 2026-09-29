$NetBSD: patch-src_dispatch__common.c,v 1.7 2019/08/31 13:50:09 nia Exp $

Deal with hardcoded libGL locations and versions; let the EGL and GLES
library names be set from outside (IRIX: full paths, as rld's dlopen does
not search the library's own run path).

Without RTLD_NOLOAD (IRIX), load the library to find out what is current:
the answer is the same.

IRIX: EPOXY_EGL_LIB and EPOXY_GLES2_LIB choose another EGL and GLES
implementation at run time (irix-egl-gles beside Mesa while both exist).

--- src/dispatch_common.c.orig
+++ src/dispatch_common.c
@@ -174,7 +174,9 @@
 #include "dispatch_common.h"
 
 #if defined(__APPLE__)
+#ifndef GLX_LIB
 #define GLX_LIB "/opt/X11/lib/libGL.1.dylib"
+#endif
 #define OPENGL_LIB "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
 #define GLES1_LIB "libGLESv1_CM.so"
 #define GLES2_LIB "libGLESv2.so"
@@ -189,13 +191,21 @@
 #define GLES2_LIB "libGLESv2.dll"
 #define OPENGL_LIB "OPENGL32"
 #else
-#define GLVND_GLX_LIB "libGLX.so.1"
-#define GLX_LIB "libGL.so.1"
-#define EGL_LIB "libEGL.so.1"
-#define GLES1_LIB "libGLESv1_CM.so.1"
-#define GLES2_LIB "libGLESv2.so.2"
-#define OPENGL_LIB "libOpenGL.so.0"
+#define GLVND_GLX_LIB "libGLX.so"
+#ifndef GLX_LIB
+#define GLX_LIB "libGL.so"
+#endif
+#ifndef EGL_LIB
+#define EGL_LIB "libEGL.so"
 #endif
+#ifndef GLES1_LIB
+#define GLES1_LIB "libGLESv1_CM.so"
+#endif
+#ifndef GLES2_LIB
+#define GLES2_LIB "libGLESv2.so"
+#endif
+#define OPENGL_LIB "libOpenGL.so"
+#endif
 
 #ifdef __GNUC__
 #define CONSTRUCT(_func) static void _func (void) __attribute__((constructor));
@@ -306,8 +316,23 @@
     pthread_mutex_lock(&api.mutex);
     if (!*handle) {
         int flags = RTLD_LAZY | RTLD_LOCAL;
+#ifdef RTLD_NOLOAD
         if (!load)
             flags |= RTLD_NOLOAD;
+#endif
+#ifdef __sgi
+        /* EPOXY_EGL_LIB and EPOXY_GLES2_LIB name another EGL / GLES
+         * implementation to use (to compare two side by side). */
+        {
+            const char *env = NULL;
+            if (strcmp(lib_name, EGL_LIB) == 0)
+                env = getenv("EPOXY_EGL_LIB");
+            else if (strcmp(lib_name, GLES2_LIB) == 0)
+                env = getenv("EPOXY_GLES2_LIB");
+            if (env != NULL && *env != '\0')
+                lib_name = env;
+        }
+#endif
 
         *handle = dlopen(lib_name, flags);
         if (!*handle) {
