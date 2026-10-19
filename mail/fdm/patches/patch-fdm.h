$NetBSD$

IRIX: <sys/fcntl.h> defines OP_NONE (an oplock state).
IRIX: pid_t is long, so declare the hooks with it; no d_type in struct dirent; no tm_zone or tm_gmtoff in struct tm.

--- fdm.h.orig
+++ fdm.h
@@ -549,6 +549,9 @@
 	AREA_ANY
 };
 
+#ifdef OP_NONE	/* IRIX <sys/fcntl.h>: an oplock state */
+#undef OP_NONE
+#endif
 /* Expression operators. */
 enum exprop {
 	OP_NONE,
@@ -842,9 +845,9 @@
 
 /* child-deliver.c */
 int		 child_deliver(struct child *, struct io *);
-void		 child_deliver_action_hook(int, struct account *, struct msg *,
+void		 child_deliver_action_hook(pid_t, struct account *, struct msg *,
 		     struct child_deliver_data *, int *);
-void		 child_deliver_cmd_hook(int, struct account *, struct msg *,
+void		 child_deliver_cmd_hook(pid_t, struct account *, struct msg *,
 		     struct child_deliver_data *, int *);
 
 /* parent-fetch.c */
