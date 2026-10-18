$NetBSD$

IRIX: no tm_gmtoff; the offset from timezone.

--- libfdproto/dictionary_functions.c.orig
+++ libfdproto/dictionary_functions.c
@@ -359,7 +359,12 @@
 	}
 	
 	CHECK_MALLOC_DO( localtime_r(&val, &conv), return NULL);
+#ifdef __sgi
+	/* No tm_gmtoff on IRIX. */
+	_format_offs((conv.tm_isdst > 0 ? 3600 : 0) - timezone, tz_buf);
+#else
 	_format_offs(conv.tm_gmtoff, tz_buf);
+#endif
 	CHECK_MALLOC_DO( fd_dump_extend(FD_DUMP_STD_PARAMS, "%d%02d%02dT%02d%02d%02d%s", conv.tm_year+1900, conv.tm_mon+1, conv.tm_mday, conv.tm_hour, conv.tm_min, conv.tm_sec, tz_buf), return NULL);
 	return *buf;
 }
