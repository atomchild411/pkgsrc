$NetBSD: patch-src_celengine_astro.cpp,v 1.1 2013/10/27 21:21:26 dholland Exp $

Handle a tzname incompatibility between BSD and Linux.

IRIX struct tm has no tm_gmtoff/tm_zone; use the generic code paths.

--- src/celengine/astro.cpp.orig
+++ src/celengine/astro.cpp
@@ -106,7 +106,7 @@ static const LeapSecondRecord LeapSecond
 };
 
 
-#if !defined(__GNUC__) || defined(_WIN32)
+#if !defined(__GNUC__) || defined(_WIN32) || defined(__sgi)
 static const char* MonthAbbrList[12] =
 { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
 #endif
@@ -510,8 +510,8 @@ const char* astro::Date::toCStr(Format f
     static char date[255];
 
     // MinGW's libraries don't have the tm_gmtoff and tm_zone fields for
-    // struct tm.
-#if defined(__GNUC__) && !defined(_WIN32)
+    // struct tm. Neither does IRIX.
+#if defined(__GNUC__) && !defined(_WIN32) && !defined(__sgi)
     struct tm cal_time;
     memset(&cal_time, 0, sizeof(cal_time));
     cal_time.tm_year = year-1900;
@@ -522,7 +522,8 @@ const char* astro::Date::toCStr(Format f
     cal_time.tm_sec = (int)seconds;
     cal_time.tm_wday = wday;
     cal_time.tm_gmtoff = utc_offset;
-#if defined(TARGET_OS_MAC) || defined(__FreeBSD__)
+#if defined(TARGET_OS_MAC) || defined(__FreeBSD__) || defined(__NetBSD__) || \
+	defined(__OpenBSD__) || defined(__DragonFly__)
     // tm_zone is a non-const string field on the Mac and FreeBSD (why?)
     cal_time.tm_zone = const_cast<char*>(tzname.c_str());
 #else
@@ -807,7 +808,7 @@ astro::TDBtoLocal(double tdb)
             d.minute = localt->tm_min;
             d.seconds = (int) localt->tm_sec;
             d.wday = localt->tm_wday;
-        #if defined(__GNUC__) && !defined(_WIN32)
+        #if defined(__GNUC__) && !defined(_WIN32) && !defined(__sgi)
             d.utc_offset = localt->tm_gmtoff;
             d.tzname = localt->tm_zone;
         #else
