$NetBSD$

CSS grid properties, and the box alignment keywords: parse, cascade and compute them.

--- include/libcss/computed.h.orig
+++ include/libcss/computed.h
@@ -471,6 +471,55 @@ uint8_t css_computed_widows(
 uint8_t css_computed_align_content(
 		const css_computed_style *style);
 
+uint8_t css_computed_grid_template_columns(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_grid_template_rows(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_grid_template_areas(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_grid_auto_columns(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_grid_auto_rows(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_grid_column_start(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_grid_column_end(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_grid_row_start(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_grid_row_end(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_grid_auto_flow(
+		const css_computed_style *style);
+
+uint8_t css_computed_justify_items(
+		const css_computed_style *style);
+
+uint8_t css_computed_justify_self(
+		const css_computed_style *style);
+
+uint8_t css_computed_row_gap(
+		const css_computed_style *style,
+		css_fixed *length, css_unit *unit);
+
 uint8_t css_computed_align_items(
 		const css_computed_style *style);
 
