$NetBSD$

Use tm_gmtoff only where configure found it (HAVE_TM_GMTOFF); otherwise
(IRIX) use the timezone/altzone globals.

--- htmldoc/ps-pdf.cxx.orig
+++ htmldoc/ps-pdf.cxx
@@ -11652,8 +11652,10 @@ write_prolog(FILE  *out,		/* I - Output
             doc_date.tm_hour, doc_date.tm_min, doc_date.tm_sec,
 #ifdef WIN32
             (int)(_timezone / 3600));
-#else
+#elif defined(HAVE_TM_GMTOFF)
 	    (int)(doc_date.tm_gmtoff / 3600));
+#else // No tm_gmtoff (e.g. IRIX): timezone/altzone are seconds west of UTC
+	    (int)(-(doc_date.tm_isdst > 0 ? altzone : timezone) / 3600));
 #endif // WIN32
     if (doc_title != NULL)
       fprintf(out, "%%%%Title: %s\n", doc_title);
@@ -12041,8 +12043,10 @@ write_prolog(FILE  *out,		/* I - Output
             doc_date.tm_hour, doc_date.tm_min, doc_date.tm_sec,
 #ifdef WIN32
             (int)(_timezone / 3600));
-#else
+#elif defined(HAVE_TM_GMTOFF)
 	    (int)(doc_date.tm_gmtoff / 3600));
+#else // No tm_gmtoff (e.g. IRIX): timezone/altzone are seconds west of UTC
+	    (int)(-(doc_date.tm_isdst > 0 ? altzone : timezone) / 3600));
 #endif // WIN32
     write_string(out, (uchar *)temp, 0);
 
