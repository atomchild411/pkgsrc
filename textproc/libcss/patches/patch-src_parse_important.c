$NetBSD$

CSS grid properties, and the box alignment keywords: parse, cascade and compute them.

--- src/parse/important.c.orig
+++ src/parse/important.c
@@ -124,6 +124,19 @@ void css__make_style_important(css_style *style)
 					offset++; /* string table entry */
 				break;
 
+			case CSS_PROP_GRID_TEMPLATE_COLUMNS:
+			case CSS_PROP_GRID_TEMPLATE_ROWS:
+			case CSS_PROP_GRID_TEMPLATE_AREAS:
+			case CSS_PROP_GRID_AUTO_COLUMNS:
+			case CSS_PROP_GRID_AUTO_ROWS:
+			case CSS_PROP_GRID_COLUMN_START:
+			case CSS_PROP_GRID_COLUMN_END:
+			case CSS_PROP_GRID_ROW_START:
+			case CSS_PROP_GRID_ROW_END:
+				if (value == GRID_STRING_SET)
+					offset++; /* string table entry */
+				break;
+
 			case CSS_PROP_BACKGROUND_POSITION:
 				if ((value & 0xf0) == BACKGROUND_POSITION_HORZ_SET)
 					offset += 2; /* length + units */
@@ -164,6 +177,8 @@ void css__make_style_important(css_style *style)
 			case CSS_PROP_WIDTH:
 			case CSS_PROP_COLUMN_WIDTH:
 			case CSS_PROP_COLUMN_GAP:
+			case CSS_PROP_ROW_GAP:
+				assert(BOTTOM_SET == (enum op_bottom)ROW_GAP_SET);
 				assert(BOTTOM_SET == (enum op_bottom)LEFT_SET);
 				assert(BOTTOM_SET == (enum op_bottom)RIGHT_SET);
 				assert(BOTTOM_SET == (enum op_bottom)TOP_SET);
