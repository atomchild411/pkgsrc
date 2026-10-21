$NetBSD$

IRIX: without d_type in struct dirent, every entry is of unknown type (as
for DT_UNKNOWN); configure finds optreset in <getopt.h>, which
line_tools.cpp does not include: declare it.

--- src/libdar/etage.cpp.orig
+++ src/libdar/etage.cpp
@@ -155,6 +155,7 @@
 
 		    if(cache_directory_tagging)
 			is_cache_dir = cache_directory_tagging_check(dirname, ret->d_name);
+#ifdef DT_DIR
 		    switch(ret->d_type)
 		    {
 		    case DT_DIR:
@@ -169,6 +170,10 @@
 		    default:
 			fichier.push_back(cell(string(ret->d_name), inode_type::nondir));
 		    }
+#else
+			// no d_type in struct dirent (IRIX): as for DT_UNKNOWN
+		    fichier.push_back(cell(string(ret->d_name), inode_type::unknown));
+#endif
 		}
 	    }
             closedir(tmp);
