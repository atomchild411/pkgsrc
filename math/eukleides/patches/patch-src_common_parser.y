$NetBSD$

IRIX defines NULL as 0L: cast through void * to the union.

--- src/common/parser.y.orig
+++ src/common/parser.y
@@ -734,7 +734,7 @@
     {
 	set_type($1, _POINT);
 	set_type($3, _POINT);
-	PSH_(NULL);
+	PSH_((void *)NULL);
 	PSH_((void *)$3);
 	PSH_((void *)$1);
     }
@@ -924,7 +924,7 @@
 
 | NUMBER '(' ')'
     {
-	PSH_(NULL);
+	PSH_((void *)NULL);
 	XEQ_(input_num);
     }
 
@@ -1030,7 +1030,7 @@
 
 | BARYCENTER
     {
-	PSH_(NULL);
+	PSH_((void *)NULL);
 	PSH_(0.);
     }
   '(' barycenter_arg_list ')'
@@ -1157,7 +1157,7 @@
     { XEQ_(create_set); }
 
 | EMPTY
-    { PSH_(NULL); }
+    { PSH_((void *)NULL); }
 
 | set_exp '.' set_exp
     { XEQ_(catenate_sets); }
@@ -1415,7 +1415,7 @@
 
 | STRING '(' ')'
     {
-	PSH_(NULL);
+	PSH_((void *)NULL);
 	XEQ_(input_str);
     }
 
