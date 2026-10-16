$NetBSD$

IRIX: <sys/types.h> (SGI mode) brings in <sys/bsd_types.h>, which has a type
named quad; rename Fruit's quad() so the two do not collide.

--- src/pawn.h.orig
+++ src/pawn.h
@@ -57,7 +57,7 @@
 
 extern void pawn_get_info (pawn_info_t * info, const board_t * board);
 
-extern int  quad          (int y_min, int y_max, int x);
+extern int  fruit_quad          (int y_min, int y_max, int x);
 
 #endif // !defined PAWN_H
 
