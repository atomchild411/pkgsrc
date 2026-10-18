$NetBSD$

0 < i <= ntrack (and 0 <= i < nindex) compared a boolean with the bound: check the range (clang rejects chained comparisons).

--- src/lib/cd.c.orig
+++ src/lib/cd.c
@@ -144,7 +144,7 @@
 
 Track *cd_get_track (Cd *cd, int i)
 {
-	if (0 < i <= cd->ntrack)
+	if (0 < i && i <= cd->ntrack)
 		return cd->track[i - 1];
 
 	return NULL;
@@ -277,7 +277,7 @@
 
 long track_get_index (Track *track, int i)
 {
-	if (0 <= i < track->nindex)
+	if (0 <= i && i < track->nindex)
 		return track->index[i];
 
 	return -1;
