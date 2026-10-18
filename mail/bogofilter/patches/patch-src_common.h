$NetBSD$

IRIX: <unistd.h> defines EX_OK (an access(2) mode).

--- src/common.h.orig
+++ src/common.h
@@ -82,6 +82,9 @@
 		    RC_OK,
 		    RC_MORE	}  rc_t;
 
+#ifdef EX_OK	/* IRIX <unistd.h>: an access(2) mode */
+#undef EX_OK
+#endif
 typedef enum ex_e { EX_SPAM	= RC_SPAM,
 		    EX_HAM	= RC_HAM,
 		    EX_UNSURE	= RC_UNSURE,
