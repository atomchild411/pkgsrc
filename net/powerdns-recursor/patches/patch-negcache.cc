$NetBSD$

With a 32-bit time_t, uint32_t + time_t is unsigned long: compare as time_t.

--- negcache.cc.orig
+++ negcache.cc
@@ -89,7 +89,7 @@
   // We we look how old the entry is, and increase d_servedStale accordingly, taking care not to overflow
   const time_t howlong = std::max(static_cast<time_t>(1), now - entry->d_ttd);
   const uint32_t extension = std::max(1U, std::min(entry->d_orig_ttl, s_serveStaleExtensionPeriod));
-  entry->d_servedStale = std::min(entry->d_servedStale + 1 + (howlong / extension), static_cast<time_t>(s_maxServedStaleExtensions));
+  entry->d_servedStale = std::min<time_t>(entry->d_servedStale + 1 + (howlong / extension), static_cast<time_t>(s_maxServedStaleExtensions));
   entry->d_ttd = now + std::min(entry->d_orig_ttl, s_serveStaleExtensionPeriod);
 
   if (qtype == QType::ENT) {
