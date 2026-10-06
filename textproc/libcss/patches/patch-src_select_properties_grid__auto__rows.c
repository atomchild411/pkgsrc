$NetBSD$

CSS grid, box alignment keywords, gradients, border radii and shadows: new file.

--- /dev/null
+++ src/select/properties/grid_auto_rows.c
@@ -0,0 +1,65 @@
+/*
+ * This file is part of LibCSS
+ * Licensed under the MIT License,
+ *		  http://www.opensource.org/licenses/mit-license.php
+ * Copyright 2026 atomchild411
+ */
+
+#include "bytecode/bytecode.h"
+#include "bytecode/opcodes.h"
+#include "select/propset.h"
+#include "select/propget.h"
+#include "utils/utils.h"
+
+#include "select/properties/properties.h"
+#include "select/properties/helpers.h"
+
+css_error css__cascade_grid_auto_rows(uint32_t opv, css_style *style,
+		css_select_state *state)
+{
+	return css__cascade_uri_none(opv, style, state, set_grid_auto_rows);
+}
+
+css_error css__set_grid_auto_rows_from_hint(const css_hint *hint,
+		css_computed_style *style)
+{
+	css_error error;
+
+	error = set_grid_auto_rows(style, hint->status, hint->data.string);
+
+	if (hint->data.string != NULL)
+		lwc_string_unref(hint->data.string);
+
+	return error;
+}
+
+css_error css__initial_grid_auto_rows(css_select_state *state)
+{
+	return set_grid_auto_rows(state->computed, CSS_GRID_TEMPLATE_NONE, NULL);
+}
+
+css_error css__copy_grid_auto_rows(
+		const css_computed_style *from,
+		css_computed_style *to)
+{
+	lwc_string *string;
+	uint8_t type = get_grid_auto_rows(from, &string);
+
+	if (from == to) {
+		return CSS_OK;
+	}
+
+	return set_grid_auto_rows(to, type, string);
+}
+
+css_error css__compose_grid_auto_rows(const css_computed_style *parent,
+		const css_computed_style *child,
+		css_computed_style *result)
+{
+	lwc_string *string;
+	uint8_t type = get_grid_auto_rows(child, &string);
+
+	return css__copy_grid_auto_rows(
+			type == CSS_GRID_TEMPLATE_INHERIT ? parent : child,
+			result);
+}
