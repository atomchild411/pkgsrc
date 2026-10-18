$NetBSD$

IRIX: no joystick driver; empty arch hooks.

--- src/joyport/joystick.c.orig
+++ src/joyport/joystick.c
@@ -4253,3 +4253,14 @@
         joy_driver.close(joydev);
     }
 }
+
+#if defined(__sgi)
+/* No joystick driver in arch/gtk3/joystickdrv for IRIX: none. */
+void joystick_arch_init(void)
+{
+}
+
+void joystick_arch_shutdown(void)
+{
+}
+#endif
