$NetBSD$

CSS grid properties, and the box alignment keywords: parse, cascade and compute them.

--- src/select/computed.c.orig
+++ src/select/computed.c
@@ -189,6 +189,33 @@ css_error css_computed_style_destroy(css_computed_style *style)
 	if (style->i.background_image != NULL)
 		lwc_string_unref(style->i.background_image);
 
+	if (style->i.grid_template_columns != NULL)
+		lwc_string_unref(style->i.grid_template_columns);
+
+	if (style->i.grid_template_rows != NULL)
+		lwc_string_unref(style->i.grid_template_rows);
+
+	if (style->i.grid_template_areas != NULL)
+		lwc_string_unref(style->i.grid_template_areas);
+
+	if (style->i.grid_auto_columns != NULL)
+		lwc_string_unref(style->i.grid_auto_columns);
+
+	if (style->i.grid_auto_rows != NULL)
+		lwc_string_unref(style->i.grid_auto_rows);
+
+	if (style->i.grid_column_start != NULL)
+		lwc_string_unref(style->i.grid_column_start);
+
+	if (style->i.grid_column_end != NULL)
+		lwc_string_unref(style->i.grid_column_end);
+
+	if (style->i.grid_row_start != NULL)
+		lwc_string_unref(style->i.grid_row_start);
+
+	if (style->i.grid_row_end != NULL)
+		lwc_string_unref(style->i.grid_row_end);
+
 	free(style);
 
 	return CSS_OK;
@@ -1072,6 +1099,81 @@ uint8_t css_computed_align_content(const css_computed_style *style)
 	return get_align_content(style);
 }
 
+uint8_t css_computed_grid_template_columns(const css_computed_style *style,
+		lwc_string **string)
+{
+	return get_grid_template_columns(style, string);
+}
+
+uint8_t css_computed_grid_template_rows(const css_computed_style *style,
+		lwc_string **string)
+{
+	return get_grid_template_rows(style, string);
+}
+
+uint8_t css_computed_grid_template_areas(const css_computed_style *style,
+		lwc_string **string)
+{
+	return get_grid_template_areas(style, string);
+}
+
+uint8_t css_computed_grid_auto_columns(const css_computed_style *style,
+		lwc_string **string)
+{
+	return get_grid_auto_columns(style, string);
+}
+
+uint8_t css_computed_grid_auto_rows(const css_computed_style *style,
+		lwc_string **string)
+{
+	return get_grid_auto_rows(style, string);
+}
+
+uint8_t css_computed_grid_column_start(const css_computed_style *style,
+		lwc_string **string)
+{
+	return get_grid_column_start(style, string);
+}
+
+uint8_t css_computed_grid_column_end(const css_computed_style *style,
+		lwc_string **string)
+{
+	return get_grid_column_end(style, string);
+}
+
+uint8_t css_computed_grid_row_start(const css_computed_style *style,
+		lwc_string **string)
+{
+	return get_grid_row_start(style, string);
+}
+
+uint8_t css_computed_grid_row_end(const css_computed_style *style,
+		lwc_string **string)
+{
+	return get_grid_row_end(style, string);
+}
+
+uint8_t css_computed_grid_auto_flow(const css_computed_style *style)
+{
+	return get_grid_auto_flow(style);
+}
+
+uint8_t css_computed_justify_items(const css_computed_style *style)
+{
+	return get_justify_items(style);
+}
+
+uint8_t css_computed_justify_self(const css_computed_style *style)
+{
+	return get_justify_self(style);
+}
+
+uint8_t css_computed_row_gap(const css_computed_style *style,
+		css_fixed *length, css_unit *unit)
+{
+	return get_row_gap(style, length, unit);
+}
+
 uint8_t css_computed_align_items(const css_computed_style *style)
 {
 	return get_align_items(style);
@@ -1355,6 +1457,14 @@ css_error css__compute_absolute_values(const css_computed_style *parent,
 	if (error != CSS_OK)
 		return error;
 
+	/* Fix up row-gap */
+	error = compute_absolute_length(style,
+			&ex_size.data.length,
+			get_row_gap,
+			set_row_gap);
+	if (error != CSS_OK)
+		return error;
+
 	return CSS_OK;
 }
 
