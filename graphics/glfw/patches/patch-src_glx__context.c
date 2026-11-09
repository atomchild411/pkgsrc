$NetBSD$

IRIX: the X window itself as the GLX drawable. IRIX's GLX refuses a
GLXWindow (from glXCreateWindow) as the drawable to make current
(GLXBadDrawable), so no GLFW window could get a context.

--- src/glx_context.c.orig
+++ src/glx_context.c
@@ -237,7 +237,9 @@
 {
     if (window->context.glx.window)
     {
+#if !defined(__sgi)
         glXDestroyWindow(_glfw.x11.display, window->context.glx.window);
+#endif
         window->context.glx.window = None;
     }
 
@@ -618,8 +620,14 @@
         return GLFW_FALSE;
     }
 
+#if defined(__sgi)
+    // IRIX's GLX refuses a GLXWindow as the drawable to make current
+    // (GLXBadDrawable); the X window itself is a GLX drawable there.
+    window->context.glx.window = window->x11.handle;
+#else
     window->context.glx.window =
         glXCreateWindow(_glfw.x11.display, native, window->x11.handle, NULL);
+#endif
     if (!window->context.glx.window)
     {
         _glfwInputError(GLFW_PLATFORM_ERROR, "GLX: Failed to create window");
