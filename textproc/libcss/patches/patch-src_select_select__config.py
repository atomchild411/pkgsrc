$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: parse, cascade and compute them.

--- src/select/select_config.py.orig
+++ src/select/select_config.py
@@ -61,6 +61,9 @@ style = {
     ('unicode_bidi', 2),
     ('visibility', 2),
     ('white_space', 3),
+    ('grid_auto_flow', 3),
+    ('justify_items', 4),
+    ('justify_self', 4),
     # Style group, with additional value
     ('background_color', 2, 'color'),
     ('background_image', 1, 'string'),
@@ -106,6 +109,21 @@ style = {
     ('vertical_align', 4, 'length', 'CSS_VERTICAL_ALIGN_SET'),
     ('width', 2, 'length', 'CSS_WIDTH_SET'),
     ('z_index', 2, 'integer'),
+    ('grid_template_columns', 1, 'string'),
+    ('grid_template_rows', 1, 'string'),
+    ('grid_template_areas', 1, 'string'),
+    ('grid_auto_columns', 1, 'string'),
+    ('grid_auto_rows', 1, 'string'),
+    ('grid_column_start', 1, 'string'),
+    ('grid_column_end', 1, 'string'),
+    ('grid_row_start', 1, 'string'),
+    ('grid_row_end', 1, 'string'),
+    ('border_top_left_radius', 1, 'string'),
+    ('border_top_right_radius', 1, 'string'),
+    ('border_bottom_right_radius', 1, 'string'),
+    ('border_bottom_left_radius', 1, 'string'),
+    ('box_shadow', 1, 'string'),
+    ('text_shadow', 1, 'string'),
     # Style group, arrays
     ('font_family', 3, 'string_arr', None, None,
         'Encode font family as an array of string objects, terminated with a '
@@ -133,6 +151,8 @@ style = {
     ('column_fill', 2, None, None, 'CSS_COLUMN_FILL_BALANCE'),
     ('column_gap', 2, 'length',
         'CSS_COLUMN_GAP_SET', 'CSS_COLUMN_GAP_NORMAL'),
+    ('row_gap', 2, 'length',
+        'CSS_ROW_GAP_SET', 'CSS_ROW_GAP_NORMAL'),
     ('column_rule_color', 2, 'color', None,
         'CSS_COLUMN_RULE_COLOR_CURRENT_COLOR'),
     ('column_rule_style', 4, None, None, 'CSS_COLUMN_RULE_STYLE_NONE'),
