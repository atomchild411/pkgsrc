$NetBSD$

Copied ASTs: start each node on ZEND_MM_ALIGNMENT (see zend_ast_tree_size).

--- Zend/zend_ast.c.orig
+++ Zend/zend_ast.c
@@ -1066,17 +1066,21 @@
 	return zend_ast_evaluate_ex(result, ast, scope, &short_circuited, &ctx);
 }
 
+/* zend_ast_tree_size() and zend_ast_tree_copy() pack the nodes of a tree
+ * into one block: start each node on ZEND_MM_ALIGNMENT. With 32-bit
+ * pointers zend_ast_size(n) is 12 + 4 * (n - 1), which put the nodes after
+ * it (zvals in zend_ast_zval) off their 8-byte alignment: SIGBUS on MIPS n32. */
 static size_t ZEND_FASTCALL zend_ast_tree_size(zend_ast *ast)
 {
 	size_t size;
 
 	if (ast->kind == ZEND_AST_ZVAL || ast->kind == ZEND_AST_CONSTANT) {
-		size = sizeof(zend_ast_zval);
+		size = ZEND_MM_ALIGNED_SIZE(sizeof(zend_ast_zval));
 	} else if (zend_ast_is_list(ast)) {
 		uint32_t i;
 		zend_ast_list *list = zend_ast_get_list(ast);
 
-		size = zend_ast_list_size(list->children);
+		size = ZEND_MM_ALIGNED_SIZE(zend_ast_list_size(list->children));
 		for (i = 0; i < list->children; i++) {
 			if (list->child[i]) {
 				size += zend_ast_tree_size(list->child[i]);
@@ -1085,7 +1089,7 @@
 	} else {
 		uint32_t i, children = zend_ast_get_num_children(ast);
 
-		size = zend_ast_size(children);
+		size = ZEND_MM_ALIGNED_SIZE(zend_ast_size(children));
 		for (i = 0; i < children; i++) {
 			if (ast->child[i]) {
 				size += zend_ast_tree_size(ast->child[i]);
@@ -1103,14 +1107,14 @@
 		new->attr = ast->attr;
 		ZVAL_COPY(&new->val, zend_ast_get_zval(ast));
 		Z_LINENO(new->val) = zend_ast_get_lineno(ast);
-		buf = (void*)((char*)buf + sizeof(zend_ast_zval));
+		buf = (void*)((char*)buf + ZEND_MM_ALIGNED_SIZE(sizeof(zend_ast_zval)));
 	} else if (ast->kind == ZEND_AST_CONSTANT) {
 		zend_ast_zval *new = (zend_ast_zval*)buf;
 		new->kind = ZEND_AST_CONSTANT;
 		new->attr = ast->attr;
 		ZVAL_STR_COPY(&new->val, zend_ast_get_constant_name(ast));
 		Z_LINENO(new->val) = zend_ast_get_lineno(ast);
-		buf = (void*)((char*)buf + sizeof(zend_ast_zval));
+		buf = (void*)((char*)buf + ZEND_MM_ALIGNED_SIZE(sizeof(zend_ast_zval)));
 	} else if (zend_ast_is_list(ast)) {
 		zend_ast_list *list = zend_ast_get_list(ast);
 		zend_ast_list *new = (zend_ast_list*)buf;
@@ -1119,7 +1123,7 @@
 		new->attr = list->attr;
 		new->children = list->children;
 		new->lineno = list->lineno;
-		buf = (void*)((char*)buf + zend_ast_list_size(list->children));
+		buf = (void*)((char*)buf + ZEND_MM_ALIGNED_SIZE(zend_ast_list_size(list->children)));
 		for (i = 0; i < list->children; i++) {
 			if (list->child[i]) {
 				new->child[i] = (zend_ast*)buf;
@@ -1134,7 +1138,7 @@
 		new->kind = ast->kind;
 		new->attr = ast->attr;
 		new->lineno = ast->lineno;
-		buf = (void*)((char*)buf + zend_ast_size(children));
+		buf = (void*)((char*)buf + ZEND_MM_ALIGNED_SIZE(zend_ast_size(children)));
 		for (i = 0; i < children; i++) {
 			if (ast->child[i]) {
 				new->child[i] = (zend_ast*)buf;
