$NetBSD: patch-src_Mixfix_lexerAux.hh,v 1.2 2015/12/29 23:34:51 dholland Exp $

Fix build with newer bison.
Also take an int, for flex skeletons whose yy_n_chars is one.

--- src/Mixfix/lexerAux.hh.orig
+++ src/Mixfix/lexerAux.hh
@@ -27,7 +27,10 @@
 //extern int inStackPtr;
 //extern YY_BUFFER_STATE inStack[];
 
-void getInput(char* buf, int& result, int max_size);
+void getInput(char* buf, size_t& result, int max_size);
+// flex skeletons differ in yy_n_chars' type (yy_size_t or int).
+inline void getInput(char* buf, int& result, int max_size)
+{ size_t r; getInput(buf, r, max_size); result = static_cast<int>(r); }
 void lexerIdMode();
 void lexerTokenTreeMode(int terminatingTokens);
 void lexerCmdMode();
