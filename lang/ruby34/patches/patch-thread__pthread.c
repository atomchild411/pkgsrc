$NetBSD: patch-thread__pthread.c,v 1.1 2025/01/02 06:51:05 taca Exp $

* Avoid pass "const char *" to SET_ANOTHER_THREAD_NAME();
  pthread_setname_np().
* IRIX: set the thread stack size (IRIX has no PTHREAD_STACK_MIN), and
  take a new thread's stack from that size and its first frame: IRIX
  cannot report a running thread's stack, and Ruby raised in the new
  thread before it could handle it (Thread.new crashed).

--- thread_pthread.c.orig
+++ thread_pthread.c
@@ -2053,6 +2053,15 @@
                 th->ec->machine.stack_maxsize = size - diff;
             }
         }
+#elif defined(__sgi)
+        /* IRIX cannot report a running thread's stack (no pthread_getattr_np
+           or similar). Ruby made this thread with a stack of
+           thread_machine_stack_size bytes, nt->machine_stack_maxsize of
+           them usable: start from this frame. */
+        if (th_has_dedicated_nt(th)) {
+            th->ec->machine.stack_start = local_in_parent_frame;
+            th->ec->machine.stack_maxsize = th->nt->machine_stack_maxsize;
+        }
 #else
         rb_raise(rb_eNotImpError, "ruby engine can initialize only in the main thread");
 #endif
@@ -2086,7 +2095,7 @@
 
     CHECK_ERR(pthread_attr_init(&attr));
 
-# ifdef PTHREAD_STACK_MIN
+# if defined(PTHREAD_STACK_MIN) || defined(__sgi)
     RUBY_DEBUG_LOG("stack size: %lu", (unsigned long)stack_size);
     CHECK_ERR(pthread_attr_setstacksize(&attr, stack_size));
 # endif
@@ -2724,7 +2733,7 @@
 {
 #if defined SET_ANOTHER_THREAD_NAME || defined SET_CURRENT_THREAD_NAME
     char buf[THREAD_NAME_MAX];
-    const char *s = "";
+    char *s = "";
 # if !defined SET_ANOTHER_THREAD_NAME
     if (!pthread_equal(pthread_self(), thread_id)) return;
 # endif
