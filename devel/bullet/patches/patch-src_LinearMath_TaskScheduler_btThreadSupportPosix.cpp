$NetBSD$

IRIX: one kernel execution vehicle per thread of the pool
(pthread_setconcurrency), else the workers run one at a time.

--- src/LinearMath/TaskScheduler/btThreadSupportPosix.cpp.orig
+++ src/LinearMath/TaskScheduler/btThreadSupportPosix.cpp
@@ -276,6 +276,15 @@
 	m_mainSemaphore = createSem("main");
 	//checkPThreadFunction(sem_wait(mainSemaphore));
 
+#if defined(__sgi)
+	// IRIX's libpthread runs a program's threads on one kernel execution
+	// vehicle at first and adds more only after seconds of backlog: ask for
+	// one per thread of the pool, or the workers take turns on one CPU (and
+	// their spin-then-yield waits can livelock).
+	if (pthread_getconcurrency() < m_numThreads + 1)
+		pthread_setconcurrency(m_numThreads + 1);
+#endif
+
 	for (int i = 0; i < m_numThreads; i++)
 	{
 		btThreadStatus& threadStatus = m_activeThreadStatus[i];
