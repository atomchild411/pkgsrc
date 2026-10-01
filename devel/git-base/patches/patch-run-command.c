$NetBSD$

IRIX's <unistd.h> declares atfork_parent() and atfork_child() (an SGI
extension), which clashes with these static functions: give them git's own
names.

--- run-command.c.orig
+++ run-command.c
@@ -510,7 +510,7 @@
 			BUG("%s: %s", msg, strerror(e)); \
 	} while(0)
 
-static void atfork_prepare(struct atfork_state *as)
+static void git_atfork_prepare(struct atfork_state *as)
 {
 	sigset_t all;
 
@@ -533,7 +533,7 @@
 #endif
 }
 
-static void atfork_parent(struct atfork_state *as)
+static void git_atfork_parent(struct atfork_state *as)
 {
 #ifdef NO_PTHREADS
 	if (sigprocmask(SIG_SETMASK, &as->old, NULL))
@@ -773,7 +773,7 @@
 	}
 
 	childenv = prep_childenv(cmd->env.v);
-	atfork_prepare(&as);
+	git_atfork_prepare(&as);
 
 	/*
 	 * NOTE: In order to prevent deadlocking when using threads special
@@ -875,7 +875,7 @@
 			child_die(CHILD_ERR_SILENT);
 		child_die(CHILD_ERR_ERRNO);
 	}
-	atfork_parent(&as);
+	git_atfork_parent(&as);
 	if (cmd->pid < 0)
 		error_errno("cannot fork() for %s", cmd->args.v[0]);
 	else if (cmd->clean_on_exit)
