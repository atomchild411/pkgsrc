$NetBSD$

IRIX's <ctype.h> defines _C.

--- include/mdds/trie_map_itr.hpp.orig
+++ include/mdds/trie_map_itr.hpp
@@ -66,7 +66,7 @@
     empty_iterator
 };
 
-template<typename _TrieType, typename _C>
+template<typename _TrieType, typename _IsConst>
 struct get_node_stack_type;
 
 template<typename _TrieType>
