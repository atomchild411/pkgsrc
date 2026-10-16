$NetBSD: patch-nspr_pr_src_pthreads_ptsynch.c,v 1.3 2024/10/22 12:52:02 ryoon Exp $

* Do not use pthread_equal() for non-valid thread pointers.
  From kamin@ on source-changes-d@NetBSD.org.
  https://mail-index.netbsd.org/source-changes-d/2020/02/03/msg012143.html

https://bugzilla.mozilla.org/show_bug.cgi?id=1718838

IRIX port (pthreads, IPv4); NSPR dropped its old one.

--- nspr/pr/src/pthreads/ptsynch.c.orig
+++ nspr/pr/src/pthreads/ptsynch.c
@@ -24,6 +24,13 @@
 extern PTDebug pt_debug; /* this is shared between several modules */
 #  endif                 /* defined(DEBUG) */
 
+/* XXX, pthread_equal() is misused to compare non-valid thread pointers */
+static int
+pt_pthread_equal(pthread_t t1, pthread_t t2)
+{
+	return t1 == t2;
+}
+
 #  if defined(FREEBSD)
 /*
  * On older versions of FreeBSD, pthread_mutex_trylock returns EDEADLK.
@@ -180,9 +187,9 @@
   PR_ASSERT(lock != NULL);
   PR_ASSERT(_PT_PTHREAD_MUTEX_IS_LOCKED(lock->mutex));
   PR_ASSERT(PR_TRUE == lock->locked);
-  PR_ASSERT(pthread_equal(lock->owner, self));
+  PR_ASSERT(pt_pthread_equal(lock->owner, self));
 
-  if (!lock->locked || !pthread_equal(lock->owner, self)) {
+  if (!lock->locked || !pt_pthread_equal(lock->owner, self)) {
     return PR_FAILURE;
   }
 
@@ -206,7 +213,7 @@
    * to the correctness of PR_AssertCurrentThreadOwnsLock(), but
    * this particular order makes the assertion more likely to
    * catch errors. */
-  PR_ASSERT(lock->locked && pthread_equal(lock->owner, pthread_self()));
+  PR_ASSERT(lock->locked && pt_pthread_equal(lock->owner, pthread_self()));
 }
 
 /**************************************************************/
@@ -259,7 +266,7 @@
   _PT_Notified* notified = &cvar->lock->notified;
 
   PR_ASSERT(PR_TRUE == cvar->lock->locked);
-  PR_ASSERT(pthread_equal(cvar->lock->owner, pthread_self()));
+  PR_ASSERT(pt_pthread_equal(cvar->lock->owner, pthread_self()));
   PR_ASSERT(_PT_PTHREAD_MUTEX_IS_LOCKED(cvar->lock->mutex));
 
   while (1) {
@@ -335,7 +342,7 @@
   PR_ASSERT(_PT_PTHREAD_MUTEX_IS_LOCKED(cvar->lock->mutex));
   PR_ASSERT(PR_TRUE == cvar->lock->locked);
   /* and it better be by us */
-  PR_ASSERT(pthread_equal(cvar->lock->owner, pthread_self()));
+  PR_ASSERT(pt_pthread_equal(cvar->lock->owner, pthread_self()));
 
   if (_PT_THREAD_INTERRUPTED(thred)) {
     goto aborted;
@@ -534,7 +541,7 @@
 
   rv = pthread_mutex_lock(&mon->lock);
   PR_ASSERT(0 == rv);
-  if (pthread_equal(mon->owner, self)) {
+  if (pt_pthread_equal(mon->owner, self)) {
     count = mon->entryCount;
   }
   rv = pthread_mutex_unlock(&mon->lock);
@@ -548,7 +555,7 @@
 
   rv = pthread_mutex_lock(&mon->lock);
   PR_ASSERT(0 == rv);
-  PR_ASSERT(mon->entryCount != 0 && pthread_equal(mon->owner, pthread_self()));
+  PR_ASSERT(mon->entryCount != 0 && pt_pthread_equal(mon->owner, pthread_self()));
   rv = pthread_mutex_unlock(&mon->lock);
   PR_ASSERT(0 == rv);
 #  endif
@@ -562,7 +569,7 @@
   rv = pthread_mutex_lock(&mon->lock);
   PR_ASSERT(0 == rv);
   if (mon->entryCount != 0) {
-    if (pthread_equal(mon->owner, self)) {
+    if (pt_pthread_equal(mon->owner, self)) {
       goto done;
     }
     while (mon->entryCount != 0) {
@@ -592,8 +599,8 @@
   PR_ASSERT(0 == rv);
   /* the entries should be > 0 and we'd better be the owner */
   PR_ASSERT(mon->entryCount > 0);
-  PR_ASSERT(pthread_equal(mon->owner, self));
-  if (mon->entryCount == 0 || !pthread_equal(mon->owner, self)) {
+  PR_ASSERT(pt_pthread_equal(mon->owner, self));
+  if (mon->entryCount == 0 || !pt_pthread_equal(mon->owner, self)) {
     rv = pthread_mutex_unlock(&mon->lock);
     PR_ASSERT(0 == rv);
     return PR_FAILURE;
@@ -637,7 +644,7 @@
   /* the entries better be positive */
   PR_ASSERT(mon->entryCount > 0);
   /* and it better be owned by us */
-  PR_ASSERT(pthread_equal(mon->owner, pthread_self()));
+  PR_ASSERT(pt_pthread_equal(mon->owner, pthread_self()));
 
   /* tuck these away 'till later */
   saved_entries = mon->entryCount;
@@ -858,7 +865,7 @@
  */
 #    if (defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)) || \
         (defined(FREEBSD) && __FreeBSD_version < 1200059) ||            \
-        defined(OPENBSD) || defined(DARWIN)
+        defined(OPENBSD) || defined(DARWIN) || defined(IRIX)
 /* union semun is defined by including <sys/sem.h> */
 #    else
 /* according to X/OPEN we have to define it ourselves */
