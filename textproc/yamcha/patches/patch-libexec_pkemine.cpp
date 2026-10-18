$NetBSD: patch-libexec_pkemine.cpp,v 1.1 2012/10/03 14:40:23 marino Exp $

Fix segfault bug - "is" equals std::cin when infile == "-".  This delete
command was intended for allocated std::instream object.
make_pair with explicit template arguments takes rvalues in libc++ (C++11 signature, also in C++03 mode): construct the pairs.

--- libexec/pkemine.cpp.orig
+++ libexec/pkemine.cpp
@@ -124,7 +124,7 @@
       int pos            = projected[i].second;
       unsigned int size  = transaction[id].size();
       for (unsigned int j = pos + 1; j < size; ++j) 
-	counter[transaction[id][j]].push_back (std::make_pair<unsigned int, int>(id, j));
+	counter[transaction[id][j]].push_back (std::pair<unsigned int, int>(id, j));
     }
 
     for (std::map <unsigned int , std::vector <std::pair<unsigned int, int> > >::iterator 
@@ -191,7 +191,7 @@
        std::fill (neg_num.begin(), neg_num.end(), 0);
 
        for (unsigned int i = 0; i < transaction.size(); i++) {
-	  root.push_back (std::make_pair<unsigned int, int>(i, -1));
+	  root.push_back (std::pair<unsigned int, int>(i, -1));
 	  if (w[i] > 0) ++pos_num[cid[i]];
 	  else ++neg_num[cid[i]];
        }
@@ -250,7 +250,7 @@
   PKEMine pkemine (sigma, minsup, maxpat);
   pkemine.run  (*is, os);
    
-  if (infile == "-") delete is; 
+  if (infile != "-") delete is; 
 
   return 0;
 }
