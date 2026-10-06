$NetBSD$

CSS grid properties, and the box alignment keywords: parse, cascade and compute them.

--- src/select/properties/properties.h.orig
+++ src/select/properties/properties.h
@@ -131,6 +131,19 @@ PROPERTY_FUNCS(speak);
 PROPERTY_FUNCS(speech_rate);
 PROPERTY_FUNCS(stress);
 PROPERTY_FUNCS(stroke_opacity);
+PROPERTY_FUNCS(grid_template_columns);
+PROPERTY_FUNCS(grid_template_rows);
+PROPERTY_FUNCS(grid_template_areas);
+PROPERTY_FUNCS(grid_auto_columns);
+PROPERTY_FUNCS(grid_auto_rows);
+PROPERTY_FUNCS(grid_auto_flow);
+PROPERTY_FUNCS(grid_column_start);
+PROPERTY_FUNCS(grid_column_end);
+PROPERTY_FUNCS(grid_row_start);
+PROPERTY_FUNCS(grid_row_end);
+PROPERTY_FUNCS(row_gap);
+PROPERTY_FUNCS(justify_items);
+PROPERTY_FUNCS(justify_self);
 PROPERTY_FUNCS(table_layout);
 PROPERTY_FUNCS(text_align);
 PROPERTY_FUNCS(text_decoration);
