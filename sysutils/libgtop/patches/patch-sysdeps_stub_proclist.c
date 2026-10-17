$NetBSD$

stub (platforms libgtop has no sysdeps for, such as IRIX): proclist returns
pid_t *, as declared; add the proc_wd, proc_affinity and sysinfo calls the
stub lacks (nothing known, as for its other calls).

--- sysdeps/stub/proclist.c.orig
+++ sysdeps/stub/proclist.c
@@ -42,10 +42,49 @@
  *   On success, it returnes a pointer to a list of buf->number elements
  *   each buf->size big. The total size is stored in buf->total. */
 
-unsigned *
+pid_t *
 glibtop_get_proclist_s (glibtop *server, glibtop_proclist *buf,
 			gint64 which, gint64 arg)
 {
 	memset (buf, 0, sizeof (glibtop_proclist));
 	return NULL;
 }
+
+/* The calls added since the stub was written: nothing known, as above. */
+
+#include <glibtop/procwd.h>
+#include <glibtop/procaffinity.h>
+#include <glibtop/sysinfo.h>
+
+void
+_glibtop_init_proc_wd_s (glibtop *server)
+{
+	server->sysdeps.proc_wd = 0;
+}
+
+char **
+glibtop_get_proc_wd_s (glibtop *server, glibtop_proc_wd *buf, pid_t pid)
+{
+	memset (buf, 0, sizeof (glibtop_proc_wd));
+	return NULL;
+}
+
+void
+_glibtop_init_proc_affinity_s (glibtop *server)
+{
+	server->sysdeps.proc_affinity = 0;
+}
+
+guint16 *
+glibtop_get_proc_affinity_s (glibtop *server, glibtop_proc_affinity *buf, pid_t pid)
+{
+	memset (buf, 0, sizeof (glibtop_proc_affinity));
+	return NULL;
+}
+
+const glibtop_sysinfo *
+glibtop_get_sysinfo_s (glibtop *server)
+{
+	static glibtop_sysinfo sysinfo;
+	return &sysinfo;
+}
