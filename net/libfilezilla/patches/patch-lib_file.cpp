$NetBSD$

IRIX: no futimens().

--- lib/file.cpp.orig
+++ lib/file.cpp
@@ -550,11 +550,16 @@
 		return false;
 	}
 
+#if defined(__sgi)
+	// IRIX has no futimens() and cannot set an open descriptor's times.
+	return false;
+#else
 	struct timespec times[2]{};
 	times[0].tv_nsec = UTIME_OMIT;
 	times[1].tv_sec = t.get_time_t();
 	times[1].tv_nsec = t.get_milliseconds() * 1000000;
 	return futimens(fd_, times) == 0;
+#endif
 }
 
 datetime file::get_modification_time() const
