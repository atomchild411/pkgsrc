$NetBSD$

log_it takes a PID_T, as misc.c defines it (pid_t is long on IRIX n32).

--- funcs.h.orig
+++ funcs.h
@@ -39,7 +39,7 @@
 		free_entry(entry *),
 		acquire_daemonlock(int),
 		skip_comments(FILE *),
-		log_it(const char *, int, const char *, const char *),
+		log_it(const char *, PID_T, const char *, const char *),
 		log_close(void);
 
 int		job_runqueue(void),
