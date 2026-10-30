$NetBSD$

IRIX: no pthread_condattr_setclock(); condition waits take CLOCK_REALTIME deadlines.

--- grooveplayer/player.c.orig
+++ grooveplayer/player.c
@@ -221,7 +221,12 @@
 
         // sleep for a little while
         struct timespec tms;
+#ifdef __sgi
+        // IRIX's condition variables wait on CLOCK_REALTIME only.
+        clock_gettime(CLOCK_REALTIME, &tms);
+#else
         clock_gettime(CLOCK_MONOTONIC, &tms);
+#endif
         tms.tv_nsec += 10000000;
         pthread_cond_timedwait(&p->pause_cond, &p->play_head_mutex, &tms);
         pthread_mutex_unlock(&p->play_head_mutex);
@@ -439,7 +444,10 @@
     p->play_head_mutex_inited = true;
 
     pthread_condattr_init(&p->cond_attr);
+#ifndef __sgi
+    // IRIX has no pthread_condattr_setclock().
     pthread_condattr_setclock(&p->cond_attr, CLOCK_MONOTONIC);
+#endif
     if (pthread_cond_init(&p->pause_cond, &p->cond_attr) != 0) {
         groove_player_destroy(player);
         av_log(NULL, AV_LOG_ERROR, "unable to create mutex condition\n");
