$NetBSD$

A 1.x or 2.x compatibility-profile request needs no GLX_ARB_create_context:
where it is missing (IRIX GLX), create the legacy context, which is exactly
that, instead of failing with "OpenGL 3.0 and later are not supported".

--- src/video/x11/SDL_x11opengl.c.orig
+++ src/video/x11/SDL_x11opengl.c
@@ -724,9 +724,13 @@
     vinfo = X11_XGetVisualInfo(display, VisualScreenMask | VisualIDMask, &v, &n);
     if (vinfo) {
         if (_this->gl_config.major_version < 3 &&
-            _this->gl_config.profile_mask == 0 &&
+            (_this->gl_config.profile_mask == 0 ||
+             (_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_COMPATIBILITY &&
+              !_this->gl_data->glXCreateContextAttribsARB)) &&
             _this->gl_config.flags == 0) {
-            /* Create legacy context */
+            /* Create legacy context (also for a 1.x/2.x compatibility
+               profile where GLX_ARB_create_context is missing: the
+               legacy context is exactly that) */
             context =
                 _this->gl_data->glXCreateContext(display, vinfo, share_context, True);
         } else {
