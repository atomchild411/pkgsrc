$NetBSD$

IRIX joystick driver (src/joystick/irix).

--- src/joystick/SDL_joystick.c.orig
+++ src/joystick/SDL_joystick.c
@@ -70,6 +70,9 @@
 #ifdef SDL_JOYSTICK_LINUX
     &SDL_LINUX_JoystickDriver,
 #endif
+#ifdef SDL_JOYSTICK_IRIX
+    &SDL_IRIX_JoystickDriver,
+#endif
 #ifdef SDL_JOYSTICK_IOKIT
     &SDL_DARWIN_JoystickDriver,
 #endif
