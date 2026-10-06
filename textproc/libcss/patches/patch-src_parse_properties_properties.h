$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: parse, cascade and compute them.

--- src/parse/properties/properties.h.orig
+++ src/parse/properties/properties.h
@@ -460,6 +460,90 @@ css_error css__parse_word_spacing(css_language *c,
 css_error css__parse_writing_mode(css_language *c,
 		const parserutils_vector *vector, int32_t *ctx,
 		css_style *result);
+css_error css__parse_gap(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_area(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_auto_columns(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_auto_flow(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_auto_rows(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_column(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_column_end(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_column_gap(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_column_start(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_gap(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_row(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_row_end(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_row_gap(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_row_start(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_template(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_template_areas(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_template_columns(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_grid_template_rows(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_justify_items(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_justify_self(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_row_gap(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_border_radius(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_border_bottom_left_radius(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_border_bottom_right_radius(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_border_top_left_radius(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_border_top_right_radius(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_box_shadow(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
+css_error css__parse_text_shadow(css_language *c,
+		const parserutils_vector *vector, int32_t *ctx,
+		css_style *result);
 css_error css__parse_z_index(css_language *c,
 		const parserutils_vector *vector, int32_t *ctx,
 		css_style *result);
@@ -560,6 +644,7 @@ extern const uint32_t property_unit_mask[CSS_N_PROPERTIES];
 #define UNIT_MASK_COLUMN_COUNT          (0)
 #define UNIT_MASK_COLUMN_FILL           (0)
 #define UNIT_MASK_COLUMN_GAP            (UNIT_LENGTH)
+#define UNIT_MASK_ROW_GAP               (UNIT_LENGTH)
 #define UNIT_MASK_COLUMN_RULE_COLOR     (0)
 #define UNIT_MASK_COLUMN_RULE_STYLE     (0)
 #define UNIT_MASK_COLUMN_RULE_WIDTH     (UNIT_LENGTH)
