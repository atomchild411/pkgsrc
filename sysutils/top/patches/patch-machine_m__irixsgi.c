$NetBSD$

C99: declare proc_compares before its use; proc_owner as machine.h declares it.

--- machine/m_irixsgi.c.orig
+++ machine/m_irixsgi.c
@@ -426,6 +426,8 @@
 	return;
 }
 
+extern int (*proc_compares[])();
+
 caddr_t
 get_process_info(struct system_info *si, struct process_select *sel, int compare_index)
 
@@ -871,8 +873,8 @@
 
 
 /* return the owner of the specified process. */
-uid_t
-proc_owner(pid_t pid)
+int
+proc_owner(int pid)
 
 {
 	register struct prpsinfo *p;
