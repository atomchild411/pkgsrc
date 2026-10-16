$NetBSD$

IRIX: <sys/types.h> (SGI mode) brings in <sys/bsd_types.h>, which has a type
named quad; rename Fruit's quad() so the two do not collide.

--- src/pawn.cpp.orig
+++ src/pawn.cpp
@@ -469,16 +469,16 @@
          }
 
          if (candidate) {
-            opening[me] += quad(CandidateOpeningMin,CandidateOpeningMax,rank);
-            endgame[me] += quad(CandidateEndgameMin,CandidateEndgameMax,rank);
+            opening[me] += fruit_quad(CandidateOpeningMin,CandidateOpeningMax,rank);
+            endgame[me] += fruit_quad(CandidateEndgameMin,CandidateEndgameMax,rank);
          }
 
          // this was moved to the dynamic evaluation
 
 /*
          if (passed) {
-            opening[me] += quad(PassedOpeningMin,PassedOpeningMax,rank);
-            endgame[me] += quad(PassedEndgameMin,PassedEndgameMax,rank);
+            opening[me] += fruit_quad(PassedOpeningMin,PassedOpeningMax,rank);
+            endgame[me] += fruit_quad(PassedEndgameMin,PassedEndgameMax,rank);
          }
 */
       }
@@ -516,9 +516,9 @@
    }
 }
 
-// quad()
-
-int quad(int y_min, int y_max, int x) {
+// fruit_quad()
+
+int fruit_quad(int y_min, int y_max, int x) {
 
    int y;
 
