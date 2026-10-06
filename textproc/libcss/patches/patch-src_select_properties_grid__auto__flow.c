$NetBSD$

CSS grid properties, and the box alignment keywords: new file.

--- /dev/null
+++ src/select/properties/grid_auto_flow.c
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
+css_error css__cascade_grid_auto_flow(uint32_t opv, css_style *style,
+		css_select_state *state)
+{
+	uint16_t value = CSS_GRID_AUTO_FLOW_INHERIT;
+
+	UNUSED(style);
+
+	/* The computed values are the bytecode values, one up */
+	if (hasFlagValue(opv) == false && getValue(opv) <= GRID_AUTO_FLOW_COLUMN_DENSE)
+		value = getValue(opv) + 1;
+
+	if (css__outranks_existing(getOpcode(opv), isImportant(opv), state,
+			getFlagValue(opv))) {
+		return set_grid_auto_flow(state->computed, value);
+	}
+
+	return CSS_OK;
+}
+
+css_error css__set_grid_auto_flow_from_hint(const css_hint *hint,
+		css_computed_style *style)
+{
+	return set_grid_auto_flow(style, hint->status);
+}
+
+css_error css__initial_grid_auto_flow(css_select_state *state)
+{
+	return set_grid_auto_flow(state->computed, CSS_GRID_AUTO_FLOW_ROW);
+}
+
+css_error css__copy_grid_auto_flow(
+		const css_computed_style *from,
+		css_computed_style *to)
+{
+	if (from == to) {
+		return CSS_OK;
+	}
+
+	return set_grid_auto_flow(to, get_grid_auto_flow(from));
+}
+
+css_error css__compose_grid_auto_flow(const css_computed_style *parent,
+		const css_computed_style *child,
+		css_computed_style *result)
+{
+	uint8_t type = get_grid_auto_flow(child);
+
+	return css__copy_grid_auto_flow(
+			type == CSS_GRID_AUTO_FLOW_INHERIT ? parent : child,
+			result);
+}
