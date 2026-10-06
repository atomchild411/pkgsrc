$NetBSD$

Media query lists: a comma after a media type ends that query ("screen,
print" was read as "not all" and the rest dropped).

--- src/parse/mq.c.orig
+++ src/parse/mq.c
@@ -1046,8 +1046,10 @@
 
 	consumeWhitespace(vector, ctx);
 
-	token = parserutils_vector_iterate(vector, ctx);
-	if (token != NULL) {
+	/* A comma ends this query: the list continues after it. */
+	token = parserutils_vector_peek(vector, *ctx);
+	if (token != NULL && tokenIsChar(token, ',') == false) {
+		token = parserutils_vector_iterate(vector, ctx);
 		if (token->type != CSS_TOKEN_IDENT ||
 				lwc_string_caseless_isequal(token->idata,
 					strings[AND], &match) != lwc_error_ok ||
