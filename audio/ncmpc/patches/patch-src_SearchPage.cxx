$NetBSD$

Not constexpr: clang rejects casting SEARCH_URI (131) to mpd_tag_type, whose values fit in 6 bits, in a constant expression.

--- src/SearchPage.cxx.orig
+++ src/SearchPage.cxx
@@ -85,7 +85,7 @@
 	const char *label;
 };
 
-static constexpr SearchMode mode[] = {
+static const SearchMode mode[] = {
 	{ MPD_TAG_TITLE, N_("Title") },
 	{ MPD_TAG_ARTIST, N_("Artist") },
 	{ MPD_TAG_ALBUM, N_("Album") },
