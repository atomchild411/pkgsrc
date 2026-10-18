$NetBSD$

KeySym (c_ulong) is 32 bits on ILP32 (IRIX n32): widen it, so that try_from can fail.

--- lefthk-core/src/xwrap.rs.orig
+++ lefthk-core/src/xwrap.rs
@@ -169,7 +169,7 @@
         // Not using XKeysymToKeycode because deprecated.
         let sym =
             unsafe { (self.xlib.XkbKeycodeToKeysym)(self.display, u8::try_from(keycode)?, 0, 0) };
-        Ok(u32::try_from(sym)?)
+        Ok(u32::try_from(sym as u64)?)
     }
 
     /// Converts a keysym to a keycode.
