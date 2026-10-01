$NetBSD$

TERM=iris-*: default to 'nottyfast', so the startup queries are not sent.

--- src/nvim/option.c.orig
+++ src/nvim/option.c
@@ -409,7 +409,12 @@ void set_init_1(bool clean_arg)
 
   // Allow disabling ttyfast during startup to disable features such as
   // automatic background detection over slow connections.
-  if (os_env_exists("NVIM_NOTTYFAST", false)) {
+  // IRIX's xwsh/winterm (TERM=iris-*) answer none of the 'ttyfast' queries
+  // and print them.
+  const char *term = os_getenv_noalloc("TERM");
+  bool iris_term = term != NULL && strncmp(term, "iris", 4) == 0
+                   && (term[4] == NUL || term[4] == '-');
+  if (os_env_exists("NVIM_NOTTYFAST", false) || iris_term) {
     set_option_value_give_err(kOptTtyfast, BOOLEAN_OPTVAL(false), 0);
   }
 
