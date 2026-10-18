$NetBSD: patch-analize.c,v 1.1 2013/02/26 10:29:34 joerg Exp $

random()<1000 < param_kan meant random()%1000 < param_kan (clang rejects
the chained comparison).

--- analize.c.orig
+++ analize.c
@@ -98,7 +98,6 @@
 
 static calc_myposition();
 static analize_policy();
-static analize_base();
 static filter_random();
 static filter_dora();
 static filter_zone();
@@ -118,6 +117,8 @@
 static print_point();
 static naki_look();
 
+static void analize_base(global_t *gp, int p, int max, int *rp);
+
 static calc_myposition(gp) global_t *gp; {
         int i,j,tmp;
 	int s[4];
@@ -224,10 +225,11 @@
 
 pnt_t result_pnt;
 
+void
 #ifdef INTEST
 new_analize(gp,p) global_t *gp;
 #else
-analize(gp,p) global_t *gp;
+analize(global_t *gp, int p)
 #endif
 {
 	int r[14];
@@ -293,7 +295,7 @@
 		analize_policy(gp);
 		if (policy != POL_CHITOI && policy != POL_KOKUSHI && 
 		    (result_rest == 1
-		     || (result_rest <= 2 && random()<1000 < param_kan)))
+		     || (result_rest <= 2 && random()%1000 < param_kan)))
 			ask_attr = T_HN_KAN;
 	}
 }
@@ -608,7 +610,7 @@
 }
 
 
-static analize_base(gp,p,max,rp) global_t *gp; int *rp; {
+static void analize_base(global_t *gp, int p, int max, int *rp) {
 	ahand_t a;
 	int rests[14];
 	int r[14];
