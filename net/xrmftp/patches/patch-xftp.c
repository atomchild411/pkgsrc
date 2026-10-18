$NetBSD$

IRIX <math.h> defines flog to logf.

--- xftp.c.orig
+++ xftp.c
@@ -125,6 +125,8 @@
 int minx = 670, miny = 400;
 struct sockaddr_in serverPI, userDTP;
 FL_FORM *forms[N_FORMS];
+/* IRIX <math.h>: #define flog logf */
+#undef flog
 FILE *flog;
 
 int send_command(const char *command, const char *arg, char **pReply);
