$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: parse, cascade and compute them.

--- src/bytecode/opcodes.h.orig
+++ src/bytecode/opcodes.h
@@ -854,4 +854,44 @@ enum op_z_index {
 	Z_INDEX_AUTO			= 0x0000
 };
 
+/* grid-template-*, grid-auto-columns/-rows, grid-*-start/-end: a string
+ * (see css_grid_template_e), or none/auto */
+enum op_grid_string {
+	GRID_STRING_SET			= 0x0080,
+	GRID_STRING_NONE		= 0x0000
+};
+
+enum op_grid_auto_flow {
+	GRID_AUTO_FLOW_ROW		= 0x0000,
+	GRID_AUTO_FLOW_COLUMN		= 0x0001,
+	GRID_AUTO_FLOW_ROW_DENSE	= 0x0002,
+	GRID_AUTO_FLOW_COLUMN_DENSE	= 0x0003
+};
+
+enum op_row_gap {
+	ROW_GAP_NORMAL			= 0x0000,
+	ROW_GAP_SET			= 0x0080
+};
+
+enum op_justify_items {
+	JUSTIFY_ITEMS_NORMAL		= 0x0000,
+	JUSTIFY_ITEMS_STRETCH		= 0x0001,
+	JUSTIFY_ITEMS_START		= 0x0002,
+	JUSTIFY_ITEMS_END		= 0x0003,
+	JUSTIFY_ITEMS_CENTER		= 0x0004,
+	JUSTIFY_ITEMS_BASELINE		= 0x0005,
+	JUSTIFY_ITEMS_LEFT		= 0x0006
+};
+
+enum op_justify_self {
+	JUSTIFY_SELF_NORMAL		= 0x0000,
+	JUSTIFY_SELF_STRETCH		= 0x0001,
+	JUSTIFY_SELF_START		= 0x0002,
+	JUSTIFY_SELF_END		= 0x0003,
+	JUSTIFY_SELF_CENTER		= 0x0004,
+	JUSTIFY_SELF_BASELINE		= 0x0005,
+	JUSTIFY_SELF_LEFT		= 0x0006,
+	JUSTIFY_SELF_AUTO		= 0x0007
+};
+
 #endif
