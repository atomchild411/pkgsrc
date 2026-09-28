$NetBSD: patch-hw_kdrive_ephyr_hostx.c,v 1.3 2021/06/24 18:43:08 tnn Exp $

Fix Xephyr visual with -parent option.

Drop the unused <err.h>, which IRIX does not have.

--- hw/kdrive/ephyr/hostx.c.orig
+++ hw/kdrive/ephyr/hostx.c
@@ -36,7 +36,6 @@
 #include <string.h>             /* for memset */
 #include <errno.h>
 #include <time.h>
-#include <err.h>
 
 #include <sys/ipc.h>
 #include <sys/shm.h>
@@ -622,7 +621,7 @@
                               scrpriv->win_height,
                               0,
                               XCB_WINDOW_CLASS_COPY_FROM_PARENT,
-                              HostX.visual->visual_id,
+                              XCB_COPY_FROM_PARENT,
                               attr_mask,
                               attrs);
         }
