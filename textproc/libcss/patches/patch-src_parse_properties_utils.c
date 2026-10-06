$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: parse, cascade and compute them.

--- src/parse/properties/utils.c.orig
+++ src/parse/properties/utils.c
@@ -912,6 +912,160 @@ css_error css__parse_hash_colour(lwc_string *data, uint32_t *result)
  * Post condition: \a *ctx is updated with the next token to process
  *                 If the input is invalid, then \a *ctx remains unchanged.
  */
+/* ---- calc(): evaluated here when its terms come to one unit ---------- */
+
+typedef struct {
+	double v;
+	uint32_t unit;
+	bool number;	/* a plain number (no unit) */
+} calc_val;
+
+/* Absolute lengths in px (CSS 2.1: 96 px to the inch) */
+static bool calc_absolute(calc_val *a)
+{
+	switch (a->unit) {
+	case UNIT_PX: return true;
+	case UNIT_IN: a->v *= 96; break;
+	case UNIT_CM: a->v *= 96 / 2.54; break;
+	case UNIT_MM: a->v *= 96 / 25.4; break;
+	case UNIT_Q: a->v *= 96 / 101.6; break;
+	case UNIT_PT: a->v *= 96.0 / 72; break;
+	case UNIT_PC: a->v *= 16; break;
+	default: return false;
+	}
+	a->unit = UNIT_PX;
+	return true;
+}
+
+static bool calc_sum(css_language *c, const parserutils_vector *vector,
+		int32_t *ctx, calc_val *out);
+
+static bool calc_is_char(const css_token *t, char ch)
+{
+	return t != NULL && t->type == CSS_TOKEN_CHAR && t->idata != NULL &&
+			lwc_string_length(t->idata) == 1 &&
+			lwc_string_data(t->idata)[0] == ch;
+}
+
+static bool calc_value(css_language *c, const parserutils_vector *vector,
+		int32_t *ctx, calc_val *out)
+{
+	const css_token *token;
+	size_t consumed = 0;
+
+	consumeWhitespace(vector, ctx);
+	token = parserutils_vector_iterate(vector, ctx);
+	if (token == NULL)
+		return false;
+	out->number = false;
+	switch (token->type) {
+	case CSS_TOKEN_NUMBER:
+		out->v = FIXTOFLT(css__number_from_lwc_string(token->idata,
+				false, &consumed));
+		out->unit = 0;
+		out->number = true;
+		return true;
+	case CSS_TOKEN_PERCENTAGE:
+		out->v = FIXTOFLT(css__number_from_lwc_string(token->idata,
+				false, &consumed));
+		out->unit = UNIT_PCT;
+		return true;
+	case CSS_TOKEN_DIMENSION: {
+		const char *data = lwc_string_data(token->idata);
+		size_t len = lwc_string_length(token->idata);
+		uint32_t u = UNIT_PX;
+
+		out->v = FIXTOFLT(css__number_from_lwc_string(token->idata,
+				false, &consumed));
+		if (css__parse_unit_keyword(data + consumed, len - consumed,
+				&u) != CSS_OK)
+			return false;
+		out->unit = u;
+		return true;
+	}
+	case CSS_TOKEN_FUNCTION:
+		if (lwc_string_length(token->idata) != 4 || strncasecmp(
+				lwc_string_data(token->idata), "calc", 4) != 0)
+			return false;
+		break;
+	default:
+		if (!calc_is_char(token, '('))
+			return false;
+		break;
+	}
+	/* a nested calc( or ( */
+	if (!calc_sum(c, vector, ctx, out))
+		return false;
+	consumeWhitespace(vector, ctx);
+	return calc_is_char(parserutils_vector_iterate(vector, ctx), ')');
+}
+
+static bool calc_product(css_language *c, const parserutils_vector *vector,
+		int32_t *ctx, calc_val *out)
+{
+	if (!calc_value(c, vector, ctx, out))
+		return false;
+	for (;;) {
+		int32_t save = *ctx;
+		const css_token *op;
+		calc_val b;
+
+		consumeWhitespace(vector, ctx);
+		op = parserutils_vector_peek(vector, *ctx);
+		if (!calc_is_char(op, '*') && !calc_is_char(op, '/')) {
+			*ctx = save;
+			return true;
+		}
+		parserutils_vector_iterate(vector, ctx);
+		if (!calc_value(c, vector, ctx, &b))
+			return false;
+		if (calc_is_char(op, '*')) {
+			if (b.number) {
+				out->v *= b.v;
+			} else if (out->number) {
+				b.v *= out->v;
+				*out = b;
+			} else {
+				return false;
+			}
+		} else {
+			if (!b.number || b.v == 0)
+				return false;
+			out->v /= b.v;
+		}
+	}
+}
+
+static bool calc_sum(css_language *c, const parserutils_vector *vector,
+		int32_t *ctx, calc_val *out)
+{
+	if (!calc_product(c, vector, ctx, out))
+		return false;
+	for (;;) {
+		int32_t save = *ctx;
+		const css_token *op;
+		calc_val b;
+
+		consumeWhitespace(vector, ctx);
+		op = parserutils_vector_peek(vector, *ctx);
+		if (!calc_is_char(op, '+') && !calc_is_char(op, '-')) {
+			*ctx = save;
+			return true;
+		}
+		parserutils_vector_iterate(vector, ctx);
+		if (!calc_product(c, vector, ctx, &b))
+			return false;
+		if (out->number != b.number)
+			return false;
+		if (!out->number && out->unit != b.unit) {
+			/* different units: only if both are absolute lengths */
+			if (!calc_absolute(out) || !calc_absolute(&b))
+				return false;
+		}
+		out->v += calc_is_char(op, '+') ? b.v : -b.v;
+	}
+}
+
 css_error css__parse_unit_specifier(css_language *c,
 		const parserutils_vector *vector, int32_t *ctx,
 		uint32_t default_unit,
@@ -925,6 +1079,23 @@ css_error css__parse_unit_specifier(css_language *c,
 
 	consumeWhitespace(vector, ctx);
 
+	/* calc(): when its terms come to one unit */
+	token = parserutils_vector_peek(vector, *ctx);
+	if (token != NULL && token->type == CSS_TOKEN_FUNCTION &&
+			lwc_string_length(token->idata) == 4 &&
+			strncasecmp(lwc_string_data(token->idata), "calc", 4) == 0) {
+		calc_val v;
+
+		if (!calc_value(c, vector, ctx, &v) ||
+				(v.number && v.v != 0)) {
+			*ctx = orig_ctx;
+			return CSS_INVALID;
+		}
+		*length = FLTTOFIX(v.v);
+		*unit = v.number ? default_unit : v.unit;
+		return CSS_OK;
+	}
+
 	token = parserutils_vector_iterate(vector, ctx);
 	if (token == NULL || (token->type != CSS_TOKEN_DIMENSION &&
 			token->type != CSS_TOKEN_NUMBER &&
