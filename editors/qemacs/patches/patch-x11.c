$NetBSD$

cutils.h's fallthrough macro breaks <X11/Xfuncproto.h> (__has_c_attribute).

--- x11.c.orig
+++ x11.c
@@ -28,7 +28,12 @@
 #include <unistd.h>
 #include <fcntl.h>
 #include <signal.h>
+/* cutils.h's fallthrough macro breaks Xfuncproto.h's
+ * __has_c_attribute(fallthrough). */
+#pragma push_macro("fallthrough")
+#undef fallthrough
 #include <X11/Xlib.h>
+#pragma pop_macro("fallthrough")
 #include <X11/Xutil.h>
 #include <X11/keysym.h>
 #include <X11/Xatom.h>
