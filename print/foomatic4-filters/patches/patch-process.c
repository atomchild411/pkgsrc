$NetBSD$

Return pid_t as process.h declares (long on IRIX).

--- process.c.orig
+++ process.c
@@ -182,12 +182,12 @@
     return EXIT_PRNERR_NORETRY_BAD_SETTINGS;
 }
 
-int start_system_process(const char *name, const char *command, FILE **fdin, FILE **fdout)
+pid_t start_system_process(const char *name, const char *command, FILE **fdin, FILE **fdout)
 {
     return _start_process(name, exec_command, (void*)command, fdin, fdout, 1);
 }
 
-int start_process(const char *name, int (*proc_func)(FILE *, FILE *, void *), void *user_arg, FILE **fdin, FILE **fdout)
+pid_t start_process(const char *name, int (*proc_func)(FILE *, FILE *, void *), void *user_arg, FILE **fdin, FILE **fdout)
 {
     return _start_process(name, proc_func, user_arg, fdin, fdout, 0);
 }
