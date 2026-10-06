$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: new file.

--- /dev/null
+++ src/select/properties/box_shadow.c
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
+css_error css__cascade_box_shadow(uint32_t opv, css_style *style,
+		css_select_state *state)
+{
+	return css__cascade_uri_none(opv, style, state, set_box_shadow);
+}
+
+css_error css__set_box_shadow_from_hint(const css_hint *hint,
+		css_computed_style *style)
+{
+	css_error error;
+
+	error = set_box_shadow(style, hint->status, hint->data.string);
+
+	if (hint->data.string != NULL)
+		lwc_string_unref(hint->data.string);
+
+	return error;
+}
+
+css_error css__initial_box_shadow(css_select_state *state)
+{
+	return set_box_shadow(state->computed, CSS_SHADOW_NONE, NULL);
+}
+
+css_error css__copy_box_shadow(
+		const css_computed_style *from,
+		css_computed_style *to)
+{
+	lwc_string *string;
+	uint8_t type = get_box_shadow(from, &string);
+
+	if (from == to) {
+		return CSS_OK;
+	}
+
+	return set_box_shadow(to, type, string);
+}
+
+css_error css__compose_box_shadow(const css_computed_style *parent,
+		const css_computed_style *child,
+		css_computed_style *result)
+{
+	lwc_string *string;
+	uint8_t type = get_box_shadow(child, &string);
+
+	return css__copy_box_shadow(
+			type == CSS_SHADOW_INHERIT ? parent : child,
+			result);
+}
