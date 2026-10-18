$NetBSD$

Zero-initialize struct tm portably: IRIX has no tm_gmtoff/tm_zone, so 11 initializers are too many.

--- src/lib/object_store/DB.cpp.orig
+++ src/lib/object_store/DB.cpp
@@ -129,7 +129,7 @@
 	// The POSIX epoch is defined as the moment in time at midnight Coordinated
 	// Universal Time (UTC) of Thursday, January 1, 1970. A time_t value is
 	// the number of seconds elapsed since epoch.
-	struct tm ref_tm = {0,0,0,0,0,0,0,0,0,0,0};
+	struct tm ref_tm = {};
 	ref_tm.tm_year = 70; // Years since 1900;
 	ref_tm.tm_mday = 10; // 10th
 
@@ -477,7 +477,7 @@
 	int valuelen = sqlite3_column_bytes(_handle->_stmt, fieldidx-1);
 
 	unsigned long years,mons,days,hours,mins,secs;
-	struct tm gm_tm = {0,0,0,0,0,0,0,0,0,0,0};
+	struct tm gm_tm = {};
 	gm_tm.tm_isdst = 0; // Tell mktime not to take dst into account.
 	gm_tm.tm_year = 70; // 1970
 	gm_tm.tm_mday = 1; // 1th day of the month
