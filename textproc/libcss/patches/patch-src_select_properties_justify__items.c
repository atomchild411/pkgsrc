$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: new file.

--- /dev/null
+++ src/select/properties/justify_items.c
@@ -0,0 +1,67 @@
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
+css_error css__cascade_justify_items(uint32_t opv, css_style *style,
+		css_select_state *state)
+{
+	uint16_t value = CSS_JUSTIFY_ITEMS_INHERIT;
+
+	UNUSED(style);
+
+	/* The computed values are the bytecode values, one up */
+	if (hasFlagValue(opv) == false && getValue(opv) <= JUSTIFY_ITEMS_LEFT)
+		value = getValue(opv) + 1;
+
+	if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
+			getFlagValue(opv))) {
+		return set_justify_items(state->computed, value);
+	}
+
+	return CSS_OK;
+}
+
+css_error css__set_justify_items_from_hint(const css_hint *hint,
+		css_computed_style *style)
+{
+	return set_justify_items(style, hint->status);
+}
+
+css_error css__initial_justify_items(css_select_state *state)
+{
+	return set_justify_items(state->computed, CSS_JUSTIFY_ITEMS_NORMAL);
+}
+
+css_error css__copy_justify_items(
+		const css_computed_style *from,
+		css_computed_style *to)
+{
+	if (from == to) {
+		return CSS_OK;
+	}
+
+	return set_justify_items(to, get_justify_items(from));
+}
+
+css_error css__compose_justify_items(const css_computed_style *parent,
+		const css_computed_style *child,
+		css_computed_style *result)
+{
+	uint8_t type = get_justify_items(child);
+
+	return css__copy_justify_items(
+			type == CSS_JUSTIFY_ITEMS_INHERIT ? parent : child,
+			result);
+}
