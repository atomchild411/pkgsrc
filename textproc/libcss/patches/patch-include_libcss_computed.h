$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: parse, cascade and compute them.

--- include/libcss/computed.h.orig
+++ include/libcss/computed.h
@@ -471,6 +471,79 @@ uint8_t css_computed_widows(
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
+uint8_t css_computed_border_top_left_radius(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_border_top_right_radius(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_border_bottom_right_radius(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_border_bottom_left_radius(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_box_shadow(
+		const css_computed_style *style,
+		lwc_string **string);
+
+uint8_t css_computed_text_shadow(
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
 
