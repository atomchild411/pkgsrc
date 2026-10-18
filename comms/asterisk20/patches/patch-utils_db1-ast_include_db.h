$NetBSD: patch-utils_db1-ast_include_db.h,v 1.1 2023/12/10 06:40:20 ryoon Exp $
IRIX: its <sys/types.h> has a pgno_t of its own.

--- utils/db1-ast/include/db.h.orig
+++ utils/db1-ast/include/db.h
@@ -54,7 +54,7 @@
 
 #ifndef	__BIT_TYPES_DEFINED__
 #define	__BIT_TYPES_DEFINED__
-#if (!defined(__FreeBSD__) && !defined(__NetBSD__) && !defined(__APPLE__))
+#if (!defined(__FreeBSD__) && !defined(__NetBSD__) && !defined(__APPLE__) && !defined(__DragonFly__))
 typedef	__signed char		   int8_t;
 typedef	short			  int16_t;
 typedef	int			  int32_t;
@@ -75,6 +75,9 @@
 #endif
 
 #define	MAX_PAGE_NUMBER	0xffffffff	/* >= # of pages in a file */
+#ifdef __sgi
+#define	pgno_t	__db1_pgno_t	/* <sys/types.h> has a pgno_t */
+#endif
 typedef u_int32_t	pgno_t;
 #define	MAX_PAGE_OFFSET	65535		/* >= # of bytes in a page */
 typedef u_int16_t	indx_t;
