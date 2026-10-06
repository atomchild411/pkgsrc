$NetBSD$

CSS grid properties, and the box alignment keywords: parse, cascade and compute them.

--- src/select/dispatch.c.orig
+++ src/select/dispatch.c
@@ -522,5 +522,57 @@ struct prop_table prop_dispatch[CSS_N_PROPERTIES] = {
 	{
 		PROPERTY_FUNCS(stroke_opacity),
 		1,
+	},
+	{
+		PROPERTY_FUNCS(grid_template_columns),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(grid_template_rows),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(grid_template_areas),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(grid_auto_columns),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(grid_auto_rows),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(grid_auto_flow),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(grid_column_start),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(grid_column_end),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(grid_row_start),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(grid_row_end),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(row_gap),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(justify_items),
+		0,
+	},
+	{
+		PROPERTY_FUNCS(justify_self),
+		0,
 	}
 };
