$NetBSD$

IRIX struct tm has no tm_gmtoff; use the timezone/altzone globals.

--- src/log.c.orig
+++ src/log.c
@@ -61,6 +61,17 @@ char months[12][4] = {
 };
 
 
+#ifdef __sgi
+/*
+ * IRIX struct tm has no tm_gmtoff: use the timezone/altzone globals
+ * (seconds west of UTC). Done here because dobuf2() shadows "timezone".
+ */
+static long sgi_gmtoff(const struct tm *tm)
+{
+	return -(long)(tm->tm_isdst > 0 ? altzone : timezone);
+}
+#endif
+
 int dobuf2(struct clientparam * param, unsigned char * buf, const unsigned char *s, const unsigned char * doublec, struct tm* tm, char * format){
 	int i, j;
 	int len;
@@ -89,6 +100,8 @@ int dobuf2(struct clientparam * param, u
 	msec = tv.tv_usec / 1000;
 #ifdef _SOLARIS
 	timezone = -altzone / 60;
+#elif defined(__sgi)
+	timezone = sgi_gmtoff(tm) / 60;
 #else
 	timezone = tm->tm_gmtoff / 60;
 #endif
