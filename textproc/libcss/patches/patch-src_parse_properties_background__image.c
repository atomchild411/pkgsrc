$NetBSD$

CSS grid, box alignment keywords, gradients, border radii and shadows: new file.

--- /dev/null
+++ src/parse/properties/background_image.c
@@ -0,0 +1,234 @@
+/*
+ * This file is part of LibCSS.
+ * Licensed under the MIT License,
+ *		  http://www.opensource.org/licenses/mit-license.php
+ * Copyright 2026 atomchild411
+ */
+
+#include <assert.h>
+#include <stdlib.h>
+#include <string.h>
+#include <strings.h>
+
+#include "bytecode/bytecode.h"
+#include "bytecode/opcodes.h"
+#include "parse/properties/properties.h"
+#include "parse/properties/utils.h"
+
+/* The prefix of a gradient's "URL": the client draws the image itself from
+ * the function's text that follows (e.g. "linear-gradient(to right, red,
+ * #00f 50%)"), normalised to single spaces. */
+#define GRADIENT_PREFIX "nscss-gradient:"
+
+static bool gradient_add(char **buf, size_t *len, size_t *size,
+		const char *s, size_t n)
+{
+	if (*len + n + 1 > *size) {
+		size_t want = (*len + n + 1) * 2 + 64;
+		char *b = realloc(*buf, want);
+		if (b == NULL)
+			return false;
+		*buf = b;
+		*size = want;
+	}
+	memcpy(*buf + *len, s, n);
+	*len += n;
+	(*buf)[*len] = '\0';
+	return true;
+}
+
+static bool is_gradient(lwc_string *name)
+{
+	static const char *const names[] = {
+		"linear-gradient", "repeating-linear-gradient",
+		"radial-gradient", "repeating-radial-gradient",
+		"conic-gradient", "repeating-conic-gradient", NULL
+	};
+	int i;
+
+	for (i = 0; names[i] != NULL; i++)
+		if (lwc_string_length(name) == strlen(names[i]) &&
+				strncasecmp(lwc_string_data(name), names[i],
+				strlen(names[i])) == 0)
+			return true;
+	return false;
+}
+
+/**
+ * A gradient function (its FUNCTION token just taken): its text, through
+ * the matching ')', after GRADIENT_PREFIX.
+ *
+ * \return CSS_OK and *text (malloc'd), CSS_INVALID, CSS_NOMEM
+ */
+static css_error gradient_text(const css_token *fn,
+		const parserutils_vector *vector, int32_t *ctx, char **text)
+{
+	const css_token *token;
+	char *buf = NULL;
+	size_t len = 0, size = 0;
+	int depth = 1;
+	bool space = false, ok;
+
+	*text = NULL;
+	ok = gradient_add(&buf, &len, &size, GRADIENT_PREFIX,
+			strlen(GRADIENT_PREFIX)) &&
+		gradient_add(&buf, &len, &size, lwc_string_data(fn->idata),
+			lwc_string_length(fn->idata)) &&
+		gradient_add(&buf, &len, &size, "(", 1);
+	while (ok && depth > 0 &&
+			(token = parserutils_vector_iterate(vector, ctx)) != NULL) {
+		const char *s = token->idata ? lwc_string_data(token->idata) : "";
+		size_t n = token->idata ? lwc_string_length(token->idata) : 0;
+		bool close = token->type == CSS_TOKEN_CHAR && n == 1 && s[0] == ')';
+
+		if (token->type == CSS_TOKEN_S) {
+			space = true;
+			continue;
+		}
+		if (token->type == CSS_TOKEN_CHAR && n == 1 &&
+				(s[0] == ';' || s[0] == '{' || s[0] == '}' ||
+				s[0] == '!')) {
+			free(buf);
+			return CSS_INVALID;
+		}
+		if (close) {
+			depth--;
+			ok = gradient_add(&buf, &len, &size, ")", 1);
+			space = false;
+			continue;
+		}
+		if (space && buf[len - 1] != '(' &&
+				!(token->type == CSS_TOKEN_CHAR && n == 1 && s[0] == ','))
+			ok = gradient_add(&buf, &len, &size, " ", 1);
+		space = false;
+		switch (token->type) {
+		case CSS_TOKEN_HASH:
+			ok = ok && gradient_add(&buf, &len, &size, "#", 1) &&
+				gradient_add(&buf, &len, &size, s, n);
+			break;
+		case CSS_TOKEN_PERCENTAGE:
+			ok = ok && gradient_add(&buf, &len, &size, s, n) &&
+				gradient_add(&buf, &len, &size, "%", 1);
+			break;
+		case CSS_TOKEN_FUNCTION:
+			depth++;
+			ok = ok && gradient_add(&buf, &len, &size, s, n) &&
+				gradient_add(&buf, &len, &size, "(", 1);
+			break;
+		case CSS_TOKEN_CHAR:
+			ok = ok && gradient_add(&buf, &len, &size, s, n);
+			if (n == 1 && s[0] == ',')
+				space = true;
+			break;
+		case CSS_TOKEN_IDENT:
+		case CSS_TOKEN_NUMBER:
+		case CSS_TOKEN_DIMENSION:
+			ok = ok && gradient_add(&buf, &len, &size, s, n);
+			break;
+		default:
+			free(buf);
+			return CSS_INVALID;
+		}
+	}
+	if (!ok) {
+		free(buf);
+		return CSS_NOMEM;
+	}
+	if (depth > 0) {
+		free(buf);
+		return CSS_INVALID;
+	}
+	*text = buf;
+	return CSS_OK;
+}
+
+/**
+ * Parse background-image: none, a URL or a gradient (kept as a "URL" the
+ * client recognises by GRADIENT_PREFIX).
+ *
+ * \param c	  Parsing context
+ * \param vector  Vector of tokens to process
+ * \param ctx	  Pointer to vector iteration context
+ * \param result  resulting style
+ * \return CSS_OK on success,
+ *	   CSS_NOMEM on memory exhaustion,
+ *	   CSS_INVALID if the input is not valid
+ *
+ * Post condition: \a *ctx is updated with the next token to process
+ *		   If the input is invalid, then \a *ctx remains unchanged.
+ */
+css_error css__parse_background_image(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	int32_t orig_ctx = *ctx;
+	css_error error;
+	const css_token *token;
+	enum flag_value flag_value;
+	bool match;
+
+	token = parserutils_vector_iterate(vector, ctx);
+	if (token == NULL) {
+		*ctx = orig_ctx;
+		return CSS_INVALID;
+	}
+
+	if (token->type == CSS_TOKEN_IDENT &&
+			(flag_value = get_css_flag_value(c, token)) !=
+			FLAG_VALUE__NONE) {
+		error = css_stylesheet_style_flag_value(result, flag_value,
+				CSS_PROP_BACKGROUND_IMAGE);
+	} else if (token->type == CSS_TOKEN_IDENT &&
+			lwc_string_caseless_isequal(token->idata,
+			c->strings[NONE], &match) == lwc_error_ok && match) {
+		error = css__stylesheet_style_appendOPV(result,
+				CSS_PROP_BACKGROUND_IMAGE, 0,
+				BACKGROUND_IMAGE_NONE);
+	} else if (token->type == CSS_TOKEN_URI ||
+			(token->type == CSS_TOKEN_FUNCTION &&
+			is_gradient(token->idata))) {
+		lwc_string *uri = NULL;
+		uint32_t uri_snumber;
+
+		if (token->type == CSS_TOKEN_URI) {
+			error = c->sheet->resolve(c->sheet->resolve_pw,
+					c->sheet->url, token->idata, &uri);
+		} else {
+			char *text;
+
+			error = gradient_text(token, vector, ctx, &text);
+			if (error == CSS_OK) {
+				if (lwc_intern_string(text, strlen(text),
+						&uri) != lwc_error_ok)
+					error = CSS_NOMEM;
+				free(text);
+			}
+		}
+		if (error != CSS_OK) {
+			*ctx = orig_ctx;
+			return error;
+		}
+
+		error = css__stylesheet_string_add(c->sheet, uri, &uri_snumber);
+		if (error != CSS_OK) {
+			*ctx = orig_ctx;
+			return error;
+		}
+
+		error = css__stylesheet_style_appendOPV(result,
+				CSS_PROP_BACKGROUND_IMAGE, 0, BACKGROUND_IMAGE_URI);
+		if (error != CSS_OK) {
+			*ctx = orig_ctx;
+			return error;
+		}
+
+		error = css__stylesheet_style_append(result, uri_snumber);
+	} else {
+		error = CSS_INVALID;
+	}
+
+	if (error != CSS_OK)
+		*ctx = orig_ctx;
+
+	return error;
+}
