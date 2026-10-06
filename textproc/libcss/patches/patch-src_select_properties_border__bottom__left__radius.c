$NetBSD$

CSS grid, box alignment keywords, gradients, border radii and shadows: new file.

--- /dev/null
+++ src/select/properties/border_bottom_left_radius.c
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
+css_error css__cascade_border_bottom_left_radius(uint32_t opv, css_style *style,
+		css_select_state *state)
+{
+	return css__cascade_uri_none(opv, style, state, set_border_bottom_left_radius);
+}
+
+css_error css__set_border_bottom_left_radius_from_hint(const css_hint *hint,
+		css_computed_style *style)
+{
+	css_error error;
+
+	error = set_border_bottom_left_radius(style, hint->status, hint->data.string);
+
+	if (hint->data.string != NULL)
+		lwc_string_unref(hint->data.string);
+
+	return error;
+}
+
+css_error css__initial_border_bottom_left_radius(css_select_state *state)
+{
+	return set_border_bottom_left_radius(state->computed, CSS_BORDER_RADIUS_NONE, NULL);
+}
+
+css_error css__copy_border_bottom_left_radius(
+		const css_computed_style *from,
+		css_computed_style *to)
+{
+	lwc_string *string;
+	uint8_t type = get_border_bottom_left_radius(from, &string);
+
+	if (from == to) {
+		return CSS_OK;
+	}
+
+	return set_border_bottom_left_radius(to, type, string);
+}
+
+css_error css__compose_border_bottom_left_radius(const css_computed_style *parent,
+		const css_computed_style *child,
+		css_computed_style *result)
+{
+	lwc_string *string;
+	uint8_t type = get_border_bottom_left_radius(child, &string);
+
+	return css__copy_border_bottom_left_radius(
+			type == CSS_BORDER_RADIUS_INHERIT ? parent : child,
+			result);
+}
