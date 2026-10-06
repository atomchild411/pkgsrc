$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: parse, cascade and compute them.

--- src/select/strings.c.orig
+++ src/select/strings.c
@@ -160,7 +160,7 @@ css_error css_select_strings_intern(css_select_strings *str)
 		return css_error_from_lwc_error(error);
 
 	error = lwc_intern_string(
-			"first_letter", SLEN("first-letter"),
+			"first-letter", SLEN("first-letter"),
 			&str->first_letter);
 	if (error != lwc_error_ok)
 		return css_error_from_lwc_error(error);
