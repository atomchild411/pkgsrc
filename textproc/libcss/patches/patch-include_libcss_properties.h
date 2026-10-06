$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: parse, cascade and compute them.

--- include/libcss/properties.h.orig
+++ include/libcss/properties.h
@@ -140,6 +140,25 @@ enum css_properties_e {
 	CSS_PROP_ORDER				= 0x07b,
 	CSS_PROP_FILL_OPACITY			= 0x07c,
 	CSS_PROP_STROKE_OPACITY			= 0x07d,
+	CSS_PROP_GRID_TEMPLATE_COLUMNS		= 0x07e,
+	CSS_PROP_GRID_TEMPLATE_ROWS		= 0x07f,
+	CSS_PROP_GRID_TEMPLATE_AREAS		= 0x080,
+	CSS_PROP_GRID_AUTO_COLUMNS		= 0x081,
+	CSS_PROP_GRID_AUTO_ROWS			= 0x082,
+	CSS_PROP_GRID_AUTO_FLOW			= 0x083,
+	CSS_PROP_GRID_COLUMN_START		= 0x084,
+	CSS_PROP_GRID_COLUMN_END		= 0x085,
+	CSS_PROP_GRID_ROW_START			= 0x086,
+	CSS_PROP_GRID_ROW_END			= 0x087,
+	CSS_PROP_ROW_GAP			= 0x088,
+	CSS_PROP_JUSTIFY_ITEMS			= 0x089,
+	CSS_PROP_JUSTIFY_SELF			= 0x08a,
+	CSS_PROP_BORDER_TOP_LEFT_RADIUS		= 0x08b,
+	CSS_PROP_BORDER_TOP_RIGHT_RADIUS		= 0x08c,
+	CSS_PROP_BORDER_BOTTOM_RIGHT_RADIUS		= 0x08d,
+	CSS_PROP_BORDER_BOTTOM_LEFT_RADIUS		= 0x08e,
+	CSS_PROP_BOX_SHADOW			= 0x08f,
+	CSS_PROP_TEXT_SHADOW			= 0x090,
 
 	CSS_N_PROPERTIES
 };
@@ -905,6 +924,78 @@ enum css_z_index_e {
 	CSS_Z_INDEX_AUTO			= 0x2
 };
 
+/*
+ * Grid.  The track lists, areas and line placements are kept as a
+ * string each, in a normalised form of the value as written (tokens
+ * separated by single spaces: "100px 1fr minmax(10px, auto)",
+ * "repeat(2, 50px)", "span 2", "\"a b\" \"c d\""), for the layout
+ * engine to read; NULL is none (the track lists) or auto (the rest).
+ */
+enum css_grid_template_e {
+	CSS_GRID_TEMPLATE_INHERIT		= 0x0,
+	/* Consult pointer in struct to determine which */
+	CSS_GRID_TEMPLATE_SET			= 0x1,
+	CSS_GRID_TEMPLATE_NONE			= 0x1
+};
+
+enum css_grid_line_e {
+	CSS_GRID_LINE_INHERIT			= 0x0,
+	/* Consult pointer in struct to determine which */
+	CSS_GRID_LINE_SET			= 0x1,
+	CSS_GRID_LINE_AUTO			= 0x1
+};
+
+enum css_grid_auto_flow_e {
+	CSS_GRID_AUTO_FLOW_INHERIT		= 0x0,
+	CSS_GRID_AUTO_FLOW_ROW			= 0x1,
+	CSS_GRID_AUTO_FLOW_COLUMN		= 0x2,
+	CSS_GRID_AUTO_FLOW_ROW_DENSE		= 0x3,
+	CSS_GRID_AUTO_FLOW_COLUMN_DENSE		= 0x4
+};
+
+enum css_row_gap_e {
+	CSS_ROW_GAP_INHERIT			= 0x0,
+	CSS_ROW_GAP_SET				= 0x1,
+	CSS_ROW_GAP_NORMAL			= 0x2
+};
+
+enum css_justify_items_e {
+	CSS_JUSTIFY_ITEMS_INHERIT		= 0x0,
+	CSS_JUSTIFY_ITEMS_NORMAL		= 0x1,
+	CSS_JUSTIFY_ITEMS_STRETCH		= 0x2,
+	CSS_JUSTIFY_ITEMS_START			= 0x3,
+	CSS_JUSTIFY_ITEMS_END			= 0x4,
+	CSS_JUSTIFY_ITEMS_CENTER		= 0x5,
+	CSS_JUSTIFY_ITEMS_BASELINE		= 0x6,
+	CSS_JUSTIFY_ITEMS_LEFT			= 0x7
+};
+
+enum css_justify_self_e {
+	CSS_JUSTIFY_SELF_INHERIT		= 0x0,
+	CSS_JUSTIFY_SELF_NORMAL			= 0x1,
+	CSS_JUSTIFY_SELF_STRETCH		= 0x2,
+	CSS_JUSTIFY_SELF_START			= 0x3,
+	CSS_JUSTIFY_SELF_END			= 0x4,
+	CSS_JUSTIFY_SELF_CENTER			= 0x5,
+	CSS_JUSTIFY_SELF_BASELINE		= 0x6,
+	CSS_JUSTIFY_SELF_LEFT			= 0x7,
+	CSS_JUSTIFY_SELF_AUTO			= 0x8
+};
+
+/* border-*-radius, box-shadow and text-shadow: their text (normalised to
+ * single spaces), a string the client interprets; NULL is 0 or none */
+enum css_border_radius_e {
+	CSS_BORDER_RADIUS_INHERIT		= 0x0,
+	CSS_BORDER_RADIUS_SET			= 0x1,
+	CSS_BORDER_RADIUS_NONE			= 0x1
+};
+
+enum css_shadow_e {
+	CSS_SHADOW_INHERIT			= 0x0,
+	CSS_SHADOW_SET				= 0x1,
+	CSS_SHADOW_NONE				= 0x1
+};
+
 #ifdef __cplusplus
 }
 #endif
