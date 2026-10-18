$NetBSD$

The global stack is ambiguous with std::stack (using namespace std; libc++ headers include <stack>).

--- src/doc2html.ll.orig
+++ src/doc2html.ll
@@ -841,6 +841,9 @@
 <*>\n
 %%
 
+// Not std::stack (the file has using namespace std, and libc++'s headers
+// bring in <stack>).
+#define stack doc2html_stack
 McDArray <char *> stack;
 
 extern "C" {
