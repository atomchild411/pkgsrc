$NetBSD$

u_char is in <sys/types.h>.

--- include/Phrase.h.orig
+++ include/Phrase.h
@@ -2,6 +2,7 @@
 #define __PHRASE_H__
 
 #include <stdlib.h>
+#include <sys/types.h>
 
 typedef u_char freq_t;
 typedef u_char count_t;
