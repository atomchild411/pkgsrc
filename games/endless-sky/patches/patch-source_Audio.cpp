$NetBSD$

Rename the file-local queue: with using namespace std, it is ambiguous with std::queue wherever <queue> comes in through other headers (libc++ on IRIX).

--- source/Audio.cpp.orig
+++ source/Audio.cpp
@@ -83,7 +83,7 @@
 	// This queue keeps track of sounds that have been requested to play. Each
 	// added sound is "deferred" until the next audio position update to make
 	// sure that all sounds from a given frame start at the same time.
-	map<const Sound *, QueueEntry> queue;
+	map<const Sound *, QueueEntry> soundQueue;
 	map<const Sound *, QueueEntry> deferred;
 	thread::id mainThreadID;
 	
@@ -235,7 +235,7 @@
 	listener = listenerPosition;
 	
 	for(const auto &it : deferred)
-		queue[it.first].Add(it.second);
+		soundQueue[it.first].Add(it.second);
 	deferred.clear();
 }
 
@@ -259,7 +259,7 @@
 	// Place sounds from the main thread directly into the queue. They are from
 	// the UI, and the Engine may not be running right now to call Update().
 	if(this_thread::get_id() == mainThreadID)
-		queue[sound].Add(position - listener);
+		soundQueue[sound].Add(position - listener);
 	else
 	{
 		unique_lock<mutex> lock(audioMutex);
@@ -299,12 +299,12 @@
 	{
 		if(source.GetSound()->IsLooping())
 		{
-			auto it = queue.find(source.GetSound());
-			if(it != queue.end())
+			auto it = soundQueue.find(source.GetSound());
+			if(it != soundQueue.end())
 			{
 				source.Move(it->second);
 				newSources.push_back(source);
-				queue.erase(it);
+				soundQueue.erase(it);
 			}
 			else
 			{
@@ -349,7 +349,7 @@
 	
 	// Now, what is left in the queue is sounds that want to play, and that do
 	// not correspond to an existing source.
-	for(const auto &it : queue)
+	for(const auto &it : soundQueue)
 	{
 		// Use a recycled source if possible. Otherwise, create a new one.
 		unsigned source = 0;
@@ -378,7 +378,7 @@
 		sources.back().Move(it.second);
 		alSourcePlay(source);
 	}
-	queue.clear();
+	soundQueue.clear();
 	
 	// Queue up new buffers for the music, if necessary.
 	int buffersDone = 0;
