$NetBSD$

CSS grid, box alignment keywords, gradients, border radii and shadows: new file.

--- /dev/null
+++ src/parse/properties/grid.c
@@ -0,0 +1,708 @@
+/*
+ * This file is part of LibCSS.
+ * Licensed under the MIT License,
+ *		  http://www.opensource.org/licenses/mit-license.php
+ */
+
+/*
+ * Grid.  The track lists (grid-template-columns/-rows, grid-auto-columns/
+ * -rows), the areas and the line placements (grid-column-start ...) are
+ * kept as a string each: the value as written, its tokens separated by
+ * single spaces (see css_grid_template_e).  The layout engine reads them.
+ * grid-auto-flow is a keyword; the gaps are lengths.
+ */
+
+#include <assert.h>
+#include <string.h>
+#include <stdlib.h>
+
+#include "bytecode/bytecode.h"
+#include "bytecode/opcodes.h"
+#include "parse/properties/properties.h"
+#include "parse/properties/utils.h"
+
+/* Append S (N bytes) to the growing text. */
+static bool grid_text_add(char **buf, size_t *len, size_t *size,
+		const char *s, size_t n)
+{
+	if (*len + n + 1 > *size) {
+		size_t want = (*len + n + 1) * 2 + 32;
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
+/**
+ * The value's text: tokens up to the end, a '!' (of !important) or (with
+ * \a slash) a '/', with one space wherever there was white space.
+ *
+ * \return CSS_OK with *text (the caller's, malloc'd) and *ctx past the
+ *	   tokens taken, CSS_INVALID if there were none or one that cannot be
+ *	   in a grid value, CSS_NOMEM
+ */
+static css_error grid_text(const parserutils_vector *vector, int32_t *ctx,
+		bool slash, char **text)
+{
+	const css_token *token;
+	char *buf = NULL;
+	size_t len = 0, size = 0;
+	bool space = false;
+
+	*text = NULL;
+	while ((token = parserutils_vector_peek(vector, *ctx)) != NULL) {
+		const char *s = NULL;
+		size_t n = 0;
+		bool ok = true;
+
+		if (token->type == CSS_TOKEN_S) {
+			space = len > 0;
+			parserutils_vector_iterate(vector, ctx);
+			continue;
+		}
+		if (token->type == CSS_TOKEN_CHAR && token->idata != NULL &&
+				lwc_string_length(token->idata) == 1) {
+			char ch = lwc_string_data(token->idata)[0];
+
+			if (ch == '!' || (slash && ch == '/'))
+				break;
+			if (ch == '{' || ch == '}' || ch == ';')
+				break;
+		}
+		if (token->idata != NULL) {
+			s = lwc_string_data(token->idata);
+			n = lwc_string_length(token->idata);
+		}
+		switch (token->type) {
+		case CSS_TOKEN_IDENT:
+		case CSS_TOKEN_NUMBER:
+		case CSS_TOKEN_DIMENSION:
+		case CSS_TOKEN_CHAR:
+			break;
+		case CSS_TOKEN_PERCENTAGE:
+		case CSS_TOKEN_FUNCTION:
+		case CSS_TOKEN_STRING:
+		case CSS_TOKEN_HASH:
+			break;
+		default:
+			free(buf);
+			return CSS_INVALID;
+		}
+		if (space && !(token->type == CSS_TOKEN_CHAR && n == 1 &&
+				(s[0] == ')' || s[0] == ',' || s[0] == ']')) &&
+				!(len > 0 && (buf[len - 1] == '(' ||
+				buf[len - 1] == '[')))
+			ok = grid_text_add(&buf, &len, &size, " ", 1);
+		space = false;
+		if (ok && token->type == CSS_TOKEN_STRING)
+			ok = grid_text_add(&buf, &len, &size, "\"", 1);
+		if (ok && token->type == CSS_TOKEN_HASH)
+			ok = grid_text_add(&buf, &len, &size, "#", 1);
+		if (ok)
+			ok = grid_text_add(&buf, &len, &size, s, n);
+		if (ok && token->type == CSS_TOKEN_STRING)
+			ok = grid_text_add(&buf, &len, &size, "\"", 1);
+		if (ok && token->type == CSS_TOKEN_PERCENTAGE)
+			ok = grid_text_add(&buf, &len, &size, "%", 1);
+		if (ok && token->type == CSS_TOKEN_FUNCTION)
+			ok = grid_text_add(&buf, &len, &size, "(", 1);
+		if (ok && token->type == CSS_TOKEN_CHAR && n == 1 && s[0] == ',')
+			space = true;
+		if (!ok) {
+			free(buf);
+			return CSS_NOMEM;
+		}
+		parserutils_vector_iterate(vector, ctx);
+	}
+	if (len == 0) {
+		free(buf);
+		return CSS_INVALID;
+	}
+	*text = buf;
+	return CSS_OK;
+}
+
+/* Emit PROP with TEXT: "none" or "auto" (the initial values) as such,
+ * anything else as a string. */
+static css_error grid_emit(css_language *c, css_style *result,
+		opcode_t prop, const char *text)
+{
+	lwc_string *str;
+	uint32_t snumber;
+	css_error error;
+
+	if (strcasecmp(text, "none") == 0 || strcasecmp(text, "auto") == 0)
+		return css__stylesheet_style_appendOPV(result, prop, 0,
+				GRID_STRING_NONE);
+	if (lwc_intern_string(text, strlen(text), &str) != lwc_error_ok)
+		return CSS_NOMEM;
+	error = css__stylesheet_string_add(c->sheet, str, &snumber);
+	if (error != CSS_OK)
+		return error;
+	error = css__stylesheet_style_appendOPV(result, prop, 0,
+			GRID_STRING_SET);
+	if (error != CSS_OK)
+		return error;
+	return css__stylesheet_style_append(result, snumber);
+}
+
+/* The CSS-wide keywords (inherit, initial ...) for PROPS. */
+static bool grid_flag(css_language *c, const parserutils_vector *vector,
+		int32_t *ctx, css_style *result, const opcode_t *props,
+		int n, css_error *error)
+{
+	const css_token *token = parserutils_vector_peek(vector, *ctx);
+	enum flag_value flag_value;
+	int i;
+
+	if (token == NULL)
+		return false;
+	flag_value = get_css_flag_value(c, token);
+	if (flag_value == FLAG_VALUE__NONE)
+		return false;
+	*error = CSS_OK;
+	for (i = 0; i < n && *error == CSS_OK; i++)
+		*error = css_stylesheet_style_flag_value(result, flag_value,
+				props[i]);
+	if (*error == CSS_OK)
+		parserutils_vector_iterate(vector, ctx);
+	return true;
+}
+
+/* A longhand whose value is kept as a string. */
+static css_error grid_string_property(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result, opcode_t prop)
+{
+	int32_t orig_ctx = *ctx;
+	css_error error;
+	char *text;
+
+	if (grid_flag(c, vector, ctx, result, &prop, 1, &error))
+		return error;
+	error = grid_text(vector, ctx, false, &text);
+	if (error != CSS_OK) {
+		*ctx = orig_ctx;
+		return error;
+	}
+	error = grid_emit(c, result, prop, text);
+	free(text);
+	if (error != CSS_OK)
+		*ctx = orig_ctx;
+	return error;
+}
+
+css_error css__parse_grid_template_columns(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_GRID_TEMPLATE_COLUMNS);
+}
+
+css_error css__parse_grid_template_rows(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_GRID_TEMPLATE_ROWS);
+}
+
+css_error css__parse_grid_template_areas(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_GRID_TEMPLATE_AREAS);
+}
+
+css_error css__parse_grid_auto_columns(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_GRID_AUTO_COLUMNS);
+}
+
+css_error css__parse_grid_auto_rows(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_GRID_AUTO_ROWS);
+}
+
+css_error css__parse_grid_column_start(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_GRID_COLUMN_START);
+}
+
+css_error css__parse_grid_column_end(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_GRID_COLUMN_END);
+}
+
+css_error css__parse_grid_row_start(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_GRID_ROW_START);
+}
+
+css_error css__parse_grid_row_end(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_GRID_ROW_END);
+}
+
+/**
+ * grid-auto-flow: [ row | column ] || dense
+ */
+css_error css__parse_grid_auto_flow(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	int32_t orig_ctx = *ctx;
+	const opcode_t prop = CSS_PROP_GRID_AUTO_FLOW;
+	const css_token *token;
+	css_error error;
+	bool column = false, dense = false, dir = false;
+	int words = 0;
+	bool match;
+
+	if (grid_flag(c, vector, ctx, result, &prop, 1, &error))
+		return error;
+	while ((token = parserutils_vector_peek(vector, *ctx)) != NULL &&
+			token->type == CSS_TOKEN_IDENT && words < 2) {
+		if (!dir && lwc_string_caseless_isequal(token->idata,
+				c->strings[ROW], &match) == lwc_error_ok &&
+				match) {
+			dir = true;
+		} else if (!dir && lwc_string_caseless_isequal(token->idata,
+				c->strings[COLUMN], &match) == lwc_error_ok &&
+				match) {
+			dir = true;
+			column = true;
+		} else if (!dense && lwc_string_caseless_isequal(
+				token->idata, c->strings[DENSE], &match) ==
+				lwc_error_ok && match) {
+			dense = true;
+		} else {
+			break;
+		}
+		words++;
+		parserutils_vector_iterate(vector, ctx);
+		consumeWhitespace(vector, ctx);
+	}
+	if (words == 0) {
+		*ctx = orig_ctx;
+		return CSS_INVALID;
+	}
+	error = css__stylesheet_style_appendOPV(result, prop, 0,
+			column ? (dense ? GRID_AUTO_FLOW_COLUMN_DENSE :
+				GRID_AUTO_FLOW_COLUMN) :
+			(dense ? GRID_AUTO_FLOW_ROW_DENSE : GRID_AUTO_FLOW_ROW));
+	if (error != CSS_OK)
+		*ctx = orig_ctx;
+	return error;
+}
+
+/* Is TEXT a <custom-ident> (a line or area name)? */
+static bool grid_is_ident(const char *text)
+{
+	if (strchr(text, ' ') != NULL)
+		return false;
+	if ((text[0] >= '0' && text[0] <= '9') || text[0] == '-' ||
+			text[0] == '+')
+		return false;
+	return strcasecmp(text, "auto") != 0 && strncasecmp(text, "span", 4) != 0;
+}
+
+/* Is the next token a '/'?  (Taken if so.) */
+static bool grid_slash(const parserutils_vector *vector, int32_t *ctx)
+{
+	const css_token *token;
+
+	consumeWhitespace(vector, ctx);
+	token = parserutils_vector_peek(vector, *ctx);
+	if (token != NULL && token->type == CSS_TOKEN_CHAR &&
+			lwc_string_length(token->idata) == 1 &&
+			lwc_string_data(token->idata)[0] == '/') {
+		parserutils_vector_iterate(vector, ctx);
+		consumeWhitespace(vector, ctx);
+		return true;
+	}
+	return false;
+}
+
+/**
+ * The placement shorthands: N longhands PROPS from values separated by
+ * '/'.  A missing one is the first one if that names a line, else auto
+ * (grid-area copies the row start to the row end and the column start to
+ * the column end).
+ */
+static css_error grid_lines_shorthand(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result, const opcode_t *props, int n)
+{
+	int32_t orig_ctx = *ctx;
+	char *text[4] = { NULL, NULL, NULL, NULL };
+	css_error error;
+	int got = 0, i;
+
+	if (grid_flag(c, vector, ctx, result, props, n, &error))
+		return error;
+	do {
+		error = grid_text(vector, ctx, true, &text[got]);
+		if (error != CSS_OK)
+			goto out;
+		got++;
+	} while (got < n && grid_slash(vector, ctx));
+
+	{
+		const char *v[4];
+
+		v[0] = text[0];
+		if (n == 2) {
+			v[1] = got > 1 ? text[1] :
+				grid_is_ident(v[0]) ? v[0] : "auto";
+		} else {
+			v[1] = got > 1 ? text[1] :
+				grid_is_ident(v[0]) ? v[0] : "auto";
+			v[2] = got > 2 ? text[2] :
+				grid_is_ident(v[0]) ? v[0] : "auto";
+			v[3] = got > 3 ? text[3] :
+				grid_is_ident(v[1]) ? v[1] : "auto";
+		}
+		for (i = 0; i < n && error == CSS_OK; i++)
+			error = grid_emit(c, result, props[i], v[i]);
+	}
+out:
+	for (i = 0; i < 4; i++)
+		free(text[i]);
+	if (error != CSS_OK)
+		*ctx = orig_ctx;
+	return error;
+}
+
+css_error css__parse_grid_column(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	static const opcode_t props[2] = {
+		CSS_PROP_GRID_COLUMN_START, CSS_PROP_GRID_COLUMN_END
+	};
+	return grid_lines_shorthand(c, vector, ctx, result, props, 2);
+}
+
+css_error css__parse_grid_row(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	static const opcode_t props[2] = {
+		CSS_PROP_GRID_ROW_START, CSS_PROP_GRID_ROW_END
+	};
+	return grid_lines_shorthand(c, vector, ctx, result, props, 2);
+}
+
+css_error css__parse_grid_area(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	static const opcode_t props[4] = {
+		CSS_PROP_GRID_ROW_START, CSS_PROP_GRID_COLUMN_START,
+		CSS_PROP_GRID_ROW_END, CSS_PROP_GRID_COLUMN_END
+	};
+	return grid_lines_shorthand(c, vector, ctx, result, props, 4);
+}
+
+/**
+ * grid-template: none | <rows> / <columns> | areas with rows (strings,
+ * each with its row size) [ / <columns> ]
+ */
+css_error css__parse_grid_template(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	static const opcode_t props[3] = {
+		CSS_PROP_GRID_TEMPLATE_ROWS, CSS_PROP_GRID_TEMPLATE_COLUMNS,
+		CSS_PROP_GRID_TEMPLATE_AREAS
+	};
+	int32_t orig_ctx = *ctx;
+	char *rows = NULL, *cols = NULL;
+	css_error error;
+
+	if (grid_flag(c, vector, ctx, result, props, 3, &error))
+		return error;
+	error = grid_text(vector, ctx, true, &rows);
+	if (error != CSS_OK)
+		goto out;
+	if (grid_slash(vector, ctx)) {
+		error = grid_text(vector, ctx, false, &cols);
+		if (error != CSS_OK)
+			goto out;
+	}
+	if (strchr(rows, '"') != NULL) {
+		/* areas: the strings are the areas, the sizes beside them
+		 * the rows ("a a" 50px "b c" auto) */
+		char areas[1024], sizes[1024];
+		const char *p = rows;
+		size_t na = 0, ns = 0;
+
+		while (*p) {
+			if (*p == '"') {
+				const char *q = strchr(p + 1, '"');
+
+				if (q == NULL)
+					break;
+				if (na + (q - p) + 3 < sizeof areas) {
+					if (na)
+						areas[na++] = ' ';
+					memcpy(areas + na, p, q - p + 1);
+					na += q - p + 1;
+				}
+				/* a row with no size of its own: auto */
+				{
+					const char *r = q + 1;
+
+					while (*r == ' ')
+						r++;
+					if (*r == '"' || *r == '\0') {
+						if (ns + 6 < sizeof sizes) {
+							if (ns)
+								sizes[ns++] = ' ';
+							memcpy(sizes + ns, "auto", 4);
+							ns += 4;
+						}
+					}
+				}
+				p = q + 1;
+			} else if (*p == ' ') {
+				p++;
+			} else {
+				const char *q = p;
+
+				while (*q && *q != ' ' && *q != '"')
+					q++;
+				if (ns + (q - p) + 2 < sizeof sizes) {
+					if (ns)
+						sizes[ns++] = ' ';
+					memcpy(sizes + ns, p, q - p);
+					ns += q - p;
+				}
+				p = q;
+			}
+		}
+		areas[na] = '\0';
+		sizes[ns] = '\0';
+		error = grid_emit(c, result, CSS_PROP_GRID_TEMPLATE_AREAS,
+				na ? areas : "none");
+		if (error == CSS_OK)
+			error = grid_emit(c, result, CSS_PROP_GRID_TEMPLATE_ROWS,
+					ns ? sizes : "none");
+	} else {
+		error = grid_emit(c, result, CSS_PROP_GRID_TEMPLATE_AREAS,
+				"none");
+		if (error == CSS_OK)
+			error = grid_emit(c, result, CSS_PROP_GRID_TEMPLATE_ROWS,
+					rows);
+	}
+	if (error == CSS_OK)
+		error = grid_emit(c, result, CSS_PROP_GRID_TEMPLATE_COLUMNS,
+				cols ? cols : "none");
+out:
+	free(rows);
+	free(cols);
+	if (error != CSS_OK)
+		*ctx = orig_ctx;
+	return error;
+}
+
+/**
+ * gap (and grid-gap): <row-gap> [ <column-gap> ]; one value is both.
+ */
+css_error css__parse_gap(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	static const opcode_t props[2] = {
+		CSS_PROP_ROW_GAP, CSS_PROP_COLUMN_GAP
+	};
+	int32_t orig_ctx = *ctx, first;
+	const css_token *token;
+	css_error error;
+
+	if (grid_flag(c, vector, ctx, result, props, 2, &error))
+		return error;
+	first = *ctx;
+	error = css__parse_row_gap(c, vector, ctx, result);
+	if (error != CSS_OK) {
+		*ctx = orig_ctx;
+		return error;
+	}
+	consumeWhitespace(vector, ctx);
+	token = parserutils_vector_peek(vector, *ctx);
+	if (token == NULL || (token->type == CSS_TOKEN_CHAR &&
+			lwc_string_data(token->idata)[0] == '!')) {
+		/* one value: the column gap too */
+		int32_t again = first;
+
+		error = css__parse_column_gap(c, vector, &again, result);
+	} else {
+		error = css__parse_column_gap(c, vector, ctx, result);
+	}
+	if (error != CSS_OK)
+		*ctx = orig_ctx;
+	return error;
+}
+
+css_error css__parse_grid_gap(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return css__parse_gap(c, vector, ctx, result);
+}
+
+css_error css__parse_grid_row_gap(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return css__parse_row_gap(c, vector, ctx, result);
+}
+
+css_error css__parse_grid_column_gap(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return css__parse_column_gap(c, vector, ctx, result);
+}
+
+/* ---- border radii and shadows: kept as text too -------------------- */
+
+css_error css__parse_border_top_left_radius(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_BORDER_TOP_LEFT_RADIUS);
+}
+
+css_error css__parse_border_top_right_radius(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_BORDER_TOP_RIGHT_RADIUS);
+}
+
+css_error css__parse_border_bottom_right_radius(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_BORDER_BOTTOM_RIGHT_RADIUS);
+}
+
+css_error css__parse_border_bottom_left_radius(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_BORDER_BOTTOM_LEFT_RADIUS);
+}
+
+css_error css__parse_box_shadow(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_BOX_SHADOW);
+}
+
+css_error css__parse_text_shadow(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	return grid_string_property(c, vector, ctx, result,
+			CSS_PROP_TEXT_SHADOW);
+}
+
+/**
+ * border-radius: 1 to 4 horizontal radii [ / 1 to 4 vertical ], given out
+ * to the corners (top-left, top-right, bottom-right, bottom-left) as the
+ * margin shorthand does; each corner's text "H" or "H V".
+ */
+css_error css__parse_border_radius(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result)
+{
+	static const opcode_t props[4] = {
+		CSS_PROP_BORDER_TOP_LEFT_RADIUS, CSS_PROP_BORDER_TOP_RIGHT_RADIUS,
+		CSS_PROP_BORDER_BOTTOM_RIGHT_RADIUS,
+		CSS_PROP_BORDER_BOTTOM_LEFT_RADIUS
+	};
+	int32_t orig_ctx = *ctx;
+	css_error error;
+	char *text, *h[4], *v[4], *p, *slash, corner[128];
+	int nh = 0, nv = 0, i;
+
+	if (grid_flag(c, vector, ctx, result, props, 4, &error))
+		return error;
+	error = grid_text(vector, ctx, false, &text);
+	if (error != CSS_OK) {
+		*ctx = orig_ctx;
+		return error;
+	}
+	slash = strchr(text, '/');
+	if (slash != NULL)
+		*slash++ = '\0';
+	for (p = strtok(text, " "); p != NULL && nh < 4; p = strtok(NULL, " "))
+		h[nh++] = p;
+	if (slash != NULL)
+		for (p = strtok(slash, " "); p != NULL && nv < 4;
+				p = strtok(NULL, " "))
+			v[nv++] = p;
+	if (nh == 0 || (slash != NULL && nv == 0)) {
+		free(text);
+		*ctx = orig_ctx;
+		return CSS_INVALID;
+	}
+	/* 1: all; 2: tl+br, tr+bl; 3: tl, tr+bl, br */
+	if (nh < 2) h[1] = h[0];
+	if (nh < 3) h[2] = h[0];
+	if (nh < 4) h[3] = h[1];
+	if (nv > 0) {
+		if (nv < 2) v[1] = v[0];
+		if (nv < 3) v[2] = v[0];
+		if (nv < 4) v[3] = v[1];
+	}
+	error = CSS_OK;
+	for (i = 0; i < 4 && error == CSS_OK; i++) {
+		if (nv > 0)
+			snprintf(corner, sizeof corner, "%s %s", h[i], v[i]);
+		else
+			snprintf(corner, sizeof corner, "%s", h[i]);
+		/* (0 is no radius) */
+		error = grid_emit(c, result, props[i],
+				strcmp(corner, "0") == 0 ? "none" : corner);
+	}
+	free(text);
+	if (error != CSS_OK)
+		*ctx = orig_ctx;
+	return error;
+}
