$NetBSD$

IRIX joystick driver (src/joystick/irix).

--- src/joystick/SDL_sysjoystick.h.orig
+++ src/joystick/SDL_sysjoystick.h
@@ -244,6 +244,7 @@
 extern SDL_JoystickDriver SDL_RAWINPUT_JoystickDriver;
 extern SDL_JoystickDriver SDL_IOS_JoystickDriver;
 extern SDL_JoystickDriver SDL_LINUX_JoystickDriver;
+extern SDL_JoystickDriver SDL_IRIX_JoystickDriver;
 extern SDL_JoystickDriver SDL_VIRTUAL_JoystickDriver;
 extern SDL_JoystickDriver SDL_WGI_JoystickDriver;
 extern SDL_JoystickDriver SDL_WINDOWS_JoystickDriver;
