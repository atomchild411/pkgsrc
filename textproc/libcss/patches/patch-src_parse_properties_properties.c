$NetBSD$

CSS grid properties, and the box alignment keywords: parse, cascade and compute them.

--- src/parse/properties/properties.c.orig
+++ src/parse/properties/properties.c
@@ -158,7 +158,28 @@ const css_prop_handler property_handlers[LAST_PROP + 1 - FIRST_PROP] =
 	css__parse_width,
 	css__parse_word_spacing,
 	css__parse_writing_mode,
-	css__parse_z_index
+	css__parse_z_index,
+	css__parse_gap,
+	css__parse_grid_area,
+	css__parse_grid_auto_columns,
+	css__parse_grid_auto_flow,
+	css__parse_grid_auto_rows,
+	css__parse_grid_column,
+	css__parse_grid_column_end,
+	css__parse_grid_column_gap,
+	css__parse_grid_column_start,
+	css__parse_grid_gap,
+	css__parse_grid_row,
+	css__parse_grid_row_end,
+	css__parse_grid_row_gap,
+	css__parse_grid_row_start,
+	css__parse_grid_template,
+	css__parse_grid_template_areas,
+	css__parse_grid_template_columns,
+	css__parse_grid_template_rows,
+	css__parse_justify_items,
+	css__parse_justify_self,
+	css__parse_row_gap
 };
 
 /** Mapping from property bytecode index to bytecode unit class mask. */
@@ -289,4 +310,5 @@ const uint32_t property_unit_mask[CSS_N_PROPERTIES] = {
 	[CSS_PROP_FLEX_WRAP]             = UNIT_MASK_FLEX_WRAP,
 	[CSS_PROP_JUSTIFY_CONTENT]       = UNIT_MASK_JUSTIFY_CONTENT,
 	[CSS_PROP_ORDER]                 = UNIT_MASK_ORDER,
+	[CSS_PROP_ROW_GAP]               = UNIT_MASK_ROW_GAP,
 };
