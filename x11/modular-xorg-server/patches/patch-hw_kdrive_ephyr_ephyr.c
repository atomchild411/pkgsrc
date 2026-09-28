$NetBSD$

Keys arrived shifted on hosts whose keycodes do not start at 8 (IRIX's
Xsgi: 15): map the host's keycodes one to one, as the keysyms are.

--- hw/kdrive/ephyr/ephyr.c.orig
+++ hw/kdrive/ephyr/ephyr.c
@@ -1336,7 +1336,13 @@
         free(keySyms.map);
     }
 
-    ki->minScanCode = keySyms.minKeyCode;
+    /* The scan codes are the host's keycodes, and the keysyms above were
+     * put at those same keycodes, so map them one to one.
+     * KdEnqueueKeyboardEvent makes scan code s keycode
+     * s + KD_MIN_KEYCODE - minScanCode: with the host's minimum here, every
+     * key was shifted on a host whose keycodes do not start at 8 (IRIX's
+     * Xsgi starts at 15). */
+    ki->minScanCode = KD_MIN_KEYCODE;
     ki->maxScanCode = keySyms.maxKeyCode;
 
     if (ki->name != NULL) {
