$NetBSD$

Pass profdata (seven float[8192] arrays) to izpis() by pointer, not by
value. The 229 KB copy took clang over half an hour to compile for MIPS
n32 (register allocation and instruction selection of the copy).

--- src/filter/measure/measure_pr0file.c.orig
+++ src/filter/measure/measure_pr0file.c
@@ -261,7 +261,7 @@
 //dit=what data to display (display items flags)
 //m1,m2 marker positions as indexes into p.x arrays
 //output is written into string *str
-void izpis(profdata p, char *str, int m, int u, int m1, int m2, int dit)
+void izpis(const profdata *p, char *str, int m, int u, int m1, int m2, int dit)
 {
 int i;
 char fs[256],frs[16];
@@ -274,39 +274,39 @@
   case 0:	//display nothing
     return;
   case 1:	//display R channel
-    data[0]=p.r[m1]; data[1]=p.r[m2]; data[2]=data[1]-data[0];
-    data[3]=p.sr.avg; data[4]=p.sr.rms; data[5]=p.sr.min;
-    data[6]=p.sr.max;
+    data[0]=p->r[m1]; data[1]=p->r[m2]; data[2]=data[1]-data[0];
+    data[3]=p->sr.avg; data[4]=p->sr.rms; data[5]=p->sr.min;
+    data[6]=p->sr.max;
     break;
   case 2:	//display G channel
-    data[0]=p.g[m1]; data[1]=p.g[m2]; data[2]=data[1]-data[0];
-    data[3]=p.sg.avg; data[4]=p.sg.rms; data[5]=p.sg.min;
-    data[6]=p.sg.max;
+    data[0]=p->g[m1]; data[1]=p->g[m2]; data[2]=data[1]-data[0];
+    data[3]=p->sg.avg; data[4]=p->sg.rms; data[5]=p->sg.min;
+    data[6]=p->sg.max;
     break;
   case 3:	//display B channel
-    data[0]=p.b[m1]; data[1]=p.b[m2]; data[2]=data[1]-data[0];
-    data[3]=p.sb.avg; data[4]=p.sb.rms; data[5]=p.sb.min;
-    data[6]=p.sb.max;
+    data[0]=p->b[m1]; data[1]=p->b[m2]; data[2]=data[1]-data[0];
+    data[3]=p->sb.avg; data[4]=p->sb.rms; data[5]=p->sb.min;
+    data[6]=p->sb.max;
     break;
   case 4:	//display Y channel
-    data[0]=p.y[m1]; data[1]=p.y[m2]; data[2]=data[1]-data[0];
-    data[3]=p.sy.avg; data[4]=p.sy.rms; data[5]=p.sy.min;
-    data[6]=p.sy.max;
+    data[0]=p->y[m1]; data[1]=p->y[m2]; data[2]=data[1]-data[0];
+    data[3]=p->sy.avg; data[4]=p->sy.rms; data[5]=p->sy.min;
+    data[6]=p->sy.max;
     break;
   case 5:	//display Pr channel
-    data[0]=p.u[m1]; data[1]=p.u[m2]; data[2]=data[1]-data[0];
-    data[3]=p.su.avg; data[4]=p.su.rms; data[5]=p.su.min;
-    data[6]=p.su.max;
+    data[0]=p->u[m1]; data[1]=p->u[m2]; data[2]=data[1]-data[0];
+    data[3]=p->su.avg; data[4]=p->su.rms; data[5]=p->su.min;
+    data[6]=p->su.max;
     break;
   case 6:	//display Pb channel
-    data[0]=p.v[m1]; data[1]=p.v[m2]; data[2]=data[1]-data[0];
-    data[3]=p.sv.avg; data[4]=p.sv.rms; data[5]=p.sv.min;
-    data[6]=p.sv.max;
+    data[0]=p->v[m1]; data[1]=p->v[m2]; data[2]=data[1]-data[0];
+    data[3]=p->sv.avg; data[4]=p->sv.rms; data[5]=p->sv.min;
+    data[6]=p->sv.max;
     break;
   case 7:	//display alpha channel
-    data[0]=p.a[m1]; data[1]=p.a[m2]; data[2]=data[1]-data[0];
-    data[3]=p.sa.avg; data[4]=p.sa.rms; data[5]=p.sa.min;
-    data[6]=p.sa.max;
+    data[0]=p->a[m1]; data[1]=p->a[m2]; data[2]=data[1]-data[0];
+    data[3]=p->sa.avg; data[4]=p->sa.rms; data[5]=p->sa.min;
+    data[6]=p->sa.max;
     break;
   default:
     break;
@@ -475,7 +475,7 @@
 draw_line(s, w, h, x0+vx-5, y0+5, x0+vx-5, y0+vy-35, gray);
 
 //numeric display
-izpis(*p,string,m,u,m1,m2,dit);
+izpis(p,string,m,u,m1,m2,dit);
 sl=strlen(string);
 if (sl>((vx-55)/8))
   {
