$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: parse, cascade and compute them.

--- src/parse/important.c.orig
+++ src/parse/important.c
@@ -124,6 +124,25 @@ void css__make_style_important(css_style *style)
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
+			case CSS_PROP_BORDER_TOP_LEFT_RADIUS:
+			case CSS_PROP_BORDER_TOP_RIGHT_RADIUS:
+			case CSS_PROP_BORDER_BOTTOM_RIGHT_RADIUS:
+			case CSS_PROP_BORDER_BOTTOM_LEFT_RADIUS:
+			case CSS_PROP_BOX_SHADOW:
+			case CSS_PROP_TEXT_SHADOW:
+				if (value == GRID_STRING_SET)
+					offset++; /* string table entry */
+				break;
+
 			case CSS_PROP_BACKGROUND_POSITION:
 				if ((value & 0xf0) == BACKGROUND_POSITION_HORZ_SET)
 					offset += 2; /* length + units */
@@ -164,6 +183,8 @@ void css__make_style_important(css_style *style)
 			case CSS_PROP_WIDTH:
 			case CSS_PROP_COLUMN_WIDTH:
 			case CSS_PROP_COLUMN_GAP:
+			case CSS_PROP_ROW_GAP:
+				assert(BOTTOM_SET == (enum op_bottom)ROW_GAP_SET);
 				assert(BOTTOM_SET == (enum op_bottom)LEFT_SET);
 				assert(BOTTOM_SET == (enum op_bottom)RIGHT_SET);
 				assert(BOTTOM_SET == (enum op_bottom)TOP_SET);
