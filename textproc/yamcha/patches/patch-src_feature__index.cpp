$NetBSD$

make_pair with explicit template arguments takes rvalues in libc++ (C++11 signature, also in C++03 mode): construct the pairs.

--- src/feature_index.cpp.orig
+++ src/feature_index.cpp
@@ -147,11 +147,11 @@
 	  if (rclist[0] == "F" || rclist[0] == "f") {
 	     for (std::set<int>::iterator rit = tmp_row.begin(); rit != tmp_row.end(); ++rit) 
 	       for (std::set<int>::iterator cit = tmp_col.begin(); cit != tmp_col.end(); ++cit)
-		 feature_set.insert (std::make_pair <int, int>( *rit, *cit ) );
+		 feature_set.insert (std::pair <int, int>( *rit, *cit ) );
 	  } else {
 	     for (std::set<int>::iterator rit = tmp_row.begin(); rit != tmp_row.end(); ++rit) 
 	       for (std::set<int>::iterator cit = tmp_col.begin(); cit != tmp_col.end(); ++cit)
-		 bow_feature_set.insert (std::make_pair <int, int>( *rit, *cit ) );
+		 bow_feature_set.insert (std::pair <int, int>( *rit, *cit ) );
 	  }
 
 	} else if (size == 2 && (rclist[0] == "T" || rclist[0] == "t")) {
