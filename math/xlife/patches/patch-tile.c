$NetBSD: patch-tile.c,v 1.1 2012/10/26 20:39:57 joerg Exp $

* Include <stdlib.h>.
* redisplay(): its loop counter "state" hid the global run state, so
  "if (state==HIDE)" read an uninitialized local. Clang treats that as
  undefined and compiled callers as if redisplay() never returned:
  xlife crashed at the first redraw. Rename the counter.

--- tile.c.orig
+++ tile.c
@@ -61,6 +61,7 @@
  */
 
 #include <stddef.h>	/* we need offsetof() */
+#include <stdlib.h>
 #include "defs.h"
 #include "data.h"
 #include "tile.h"
@@ -407,7 +408,7 @@
     coord_t x,y;
     int ctr = 0;
     long tentx,tenty;
-    int state;
+    int st;	/* not "state": that is the global run state */
 
     displaystats();    
     if (state==HIDE)
@@ -416,8 +417,8 @@
 #if STATEBITS
     chgpoints[0] = chgpoints[1] = chgrects[0] = chgrects[1] = 0;
 #else    
-    for (state = 0; state < maxstates; state++)
-	chgpoints[state] = chgrects[state] = 0;
+    for (st = 0; st < maxstates; st++)
+	chgpoints[st] = chgrects[st] = 0;
 #endif
     
     for (ptr = active.tiles; ptr != NULL; ptr = ptr->next)
@@ -438,13 +439,13 @@
 		    chgpoints[1]=chgpoints[0]=0;
 		}
 #else
-		for (state = 0; state < maxstates; state++)
-		    if (chgpoints[state])
+		for (st = 0; st < maxstates; st++)
+		    if (chgpoints[st])
 		    {
-			XDrawPoints(disp,lifew,cellgc[state],
-				    points[state],chgpoints[state],
+			XDrawPoints(disp,lifew,cellgc[st],
+				    points[st],chgpoints[st],
 				    CoordModeOrigin);
-			chgpoints[state] = 0;
+			chgpoints[st] = 0;
 		    }
 #endif
 		ctr=0;
@@ -458,11 +459,11 @@
 		    XFillRectangles(disp,lifew,cellgc[1],rects[1],chgrects[1]);
 		    chgrects[1]=chgrects[0]=0;
 #else
-		    for (state = 0; state < maxstates; state++)
+		    for (st = 0; st < maxstates; st++)
 		    {
-			XFillRectangles(disp,lifew,cellgc[state],
-					rects[state],chgrects[state]);
-			chgrects[state] = 0;
+			XFillRectangles(disp,lifew,cellgc[st],
+					rects[st],chgrects[st]);
+			chgrects[st] = 0;
 		    }
 #endif
 		    ctr=0;
@@ -489,13 +490,13 @@
 		    chgpoints[1]=chgpoints[0]=0;
 		}
 #else
-		for (state = 0; state < maxstates; state++)
-		    if (chgpoints[state])
+		for (st = 0; st < maxstates; st++)
+		    if (chgpoints[st])
 		    {
-			XDrawPoints(disp,lifew,cellgc[state],
-				    points[state],chgpoints[state],
+			XDrawPoints(disp,lifew,cellgc[st],
+				    points[st],chgpoints[st],
 				    CoordModeOrigin);
-			chgpoints[state] = 0;
+			chgpoints[st] = 0;
 		    }
 #endif
 		ctr=0;
@@ -509,11 +510,11 @@
 		    XFillRectangles(disp,lifew,cellgc[1],rects[1],chgrects[1]);
 		    chgrects[1]=chgrects[0]=0;
 #else
-		    for (state = 0; state < maxstates; state++)
+		    for (st = 0; st < maxstates; st++)
 		    {
-			XFillRectangles(disp,lifew,cellgc[state],
-					rects[state],chgrects[state]);
-			chgrects[state] = 0;
+			XFillRectangles(disp,lifew,cellgc[st],
+					rects[st],chgrects[st]);
+			chgrects[st] = 0;
 		    }
 #endif
 		    ctr=0;
@@ -530,12 +531,12 @@
 	    XDrawPoints(disp,lifew,cellgc[1],points[1],chgpoints[1],CoordModeOrigin);
 	    chgpoints[1]=chgpoints[0]=0;
 #else
-	    for (state = 0; state < maxstates; state++)
+	    for (st = 0; st < maxstates; st++)
 	    {
-		XDrawPoints(disp,lifew,cellgc[state],
-			    points[state],chgpoints[state],
+		XDrawPoints(disp,lifew,cellgc[st],
+			    points[st],chgpoints[st],
 			    CoordModeOrigin);
-		chgpoints[state] = 0;
+		chgpoints[st] = 0;
 	    }
 #endif
 	}
@@ -546,11 +547,11 @@
 	    XFillRectangles(disp,lifew,cellgc[1],rects[1],chgrects[1]);
 	    chgrects[1]=chgrects[0]=0;
 #else
-	    for (state = 0; state < maxstates; state++)
+	    for (st = 0; st < maxstates; st++)
 	    {
-		XFillRectangles(disp,lifew,cellgc[state],
-				rects[state],chgrects[state]);
-		chgrects[state] = 0;
+		XFillRectangles(disp,lifew,cellgc[st],
+				rects[st],chgrects[st]);
+		chgrects[st] = 0;
 	    }
 #endif
 	}
