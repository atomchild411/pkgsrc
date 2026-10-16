$NetBSD$

IRIX: <sys/types.h> (SGI mode) brings in <sys/bsd_types.h>, which has a type
named quad; rename Fruit's quad() so the two do not collide.

--- src/eval.cpp.orig
+++ src/eval.cpp
@@ -949,7 +949,7 @@
 
          // opening scoring
 
-         op[att] += quad(PassedOpeningMin,PassedOpeningMax,rank);
+         op[att] += fruit_quad(PassedOpeningMin,PassedOpeningMax,rank);
 
          // endgame scoring init
 
@@ -976,7 +976,7 @@
          // endgame scoring
 
          eg[att] += min;
-         if (delta > 0) eg[att] += quad(0,delta,rank);
+         if (delta > 0) eg[att] += fruit_quad(0,delta,rank);
       }
    }
 
