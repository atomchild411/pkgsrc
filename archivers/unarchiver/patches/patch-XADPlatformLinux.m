$NetBSD$

IRIX has no lutimes: set a file's times with utimes, and leave a link's.

--- XADPlatformLinux.m.orig
+++ XADPlatformLinux.m
@@ -56,7 +56,12 @@
 		if(access) times[0]=[access timevalStruct];
 		if(modification) times[1]=[modification timevalStruct];
 
+#if defined(__sgi)
+		// IRIX has no lutimes: a link keeps its own times.
+		int res=islink?0:utimes(cpath,times);
+#else
 		int res=lutimes(cpath,times);
+#endif
 		if(res!=0&&res!=ENOSYS) return XADUnknownError; // TODO: better error
 	}
 
