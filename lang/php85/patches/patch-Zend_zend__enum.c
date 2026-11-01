$NetBSD$

Enum case ASTs: start each piece on ZEND_MM_ALIGNMENT. With 32-bit
pointers zend_ast_size(3) is 20, which put the zend_ast_zval children (and
their zvals) 4 bytes off their 8-byte alignment: SIGBUS on MIPS n32 (IRIX)
the first time an extension registered an enum case.

--- Zend/zend_enum.c.orig
+++ Zend/zend_enum.c
@@ -537,26 +537,30 @@
 static zend_ast_ref *create_enum_case_ast(
 		zend_string *class_name, zend_string *case_name, zval *value) {
 	// TODO: Use custom node type for enum cases?
-	size_t size = sizeof(zend_ast_ref) + zend_ast_size(3)
-		+ (value ? 3 : 2) * sizeof(zend_ast_zval);
+	/* Each piece starts on ZEND_MM_ALIGNMENT: zend_ast_zval holds a zval,
+	 * and with 32-bit pointers zend_ast_size(3) is 20, so the children
+	 * landed 4 bytes off their alignment (SIGBUS on MIPS n32). */
+	size_t size = ZEND_MM_ALIGNED_SIZE(sizeof(zend_ast_ref))
+		+ ZEND_MM_ALIGNED_SIZE(zend_ast_size(3))
+		+ (value ? 3 : 2) * ZEND_MM_ALIGNED_SIZE(sizeof(zend_ast_zval));
 	char *p = pemalloc(size, 1);
-	zend_ast_ref *ref = (zend_ast_ref *) p; p += sizeof(zend_ast_ref);
+	zend_ast_ref *ref = (zend_ast_ref *) p; p += ZEND_MM_ALIGNED_SIZE(sizeof(zend_ast_ref));
 	GC_SET_REFCOUNT(ref, 1);
 	GC_TYPE_INFO(ref) = GC_CONSTANT_AST | GC_PERSISTENT | GC_IMMUTABLE;
 
-	zend_ast *ast = (zend_ast *) p; p += zend_ast_size(3);
+	zend_ast *ast = (zend_ast *) p; p += ZEND_MM_ALIGNED_SIZE(zend_ast_size(3));
 	ast->kind = ZEND_AST_CONST_ENUM_INIT;
 	ast->attr = 0;
 	ast->lineno = 0;
 
-	ast->child[0] = (zend_ast *) p; p += sizeof(zend_ast_zval);
+	ast->child[0] = (zend_ast *) p; p += ZEND_MM_ALIGNED_SIZE(sizeof(zend_ast_zval));
 	ast->child[0]->kind = ZEND_AST_ZVAL;
 	ast->child[0]->attr = 0;
 	ZEND_ASSERT(ZSTR_IS_INTERNED(class_name));
 	ZVAL_STR(zend_ast_get_zval(ast->child[0]), class_name);
 	Z_LINENO_P(zend_ast_get_zval(ast->child[0])) = 0;
 
-	ast->child[1] = (zend_ast *) p; p += sizeof(zend_ast_zval);
+	ast->child[1] = (zend_ast *) p; p += ZEND_MM_ALIGNED_SIZE(sizeof(zend_ast_zval));
 	ast->child[1]->kind = ZEND_AST_ZVAL;
 	ast->child[1]->attr = 0;
 	ZEND_ASSERT(ZSTR_IS_INTERNED(case_name));
@@ -564,7 +568,7 @@
 	Z_LINENO_P(zend_ast_get_zval(ast->child[1])) = 0;
 
 	if (value) {
-		ast->child[2] = (zend_ast *) p; p += sizeof(zend_ast_zval);
+		ast->child[2] = (zend_ast *) p; p += ZEND_MM_ALIGNED_SIZE(sizeof(zend_ast_zval));
 		ast->child[2]->kind = ZEND_AST_ZVAL;
 		ast->child[2]->attr = 0;
 		ZEND_ASSERT(!Z_REFCOUNTED_P(value));
