$NetBSD$

CSS grid, box alignment keywords, gradients, border radii, shadows, calc() and ::first-letter: parse, cascade and compute them.

--- src/parse/propstrings.c.orig
+++ src/parse/propstrings.c
@@ -233,6 +233,34 @@ const stringmap_entry stringmap[LAST_KNOWN] = {
 	SMAP("word-spacing"),
 	SMAP("writing-mode"),
 	SMAP("z-index"),
+	SMAP("gap"),
+	SMAP("grid-area"),
+	SMAP("grid-auto-columns"),
+	SMAP("grid-auto-flow"),
+	SMAP("grid-auto-rows"),
+	SMAP("grid-column"),
+	SMAP("grid-column-end"),
+	SMAP("grid-column-gap"),
+	SMAP("grid-column-start"),
+	SMAP("grid-gap"),
+	SMAP("grid-row"),
+	SMAP("grid-row-end"),
+	SMAP("grid-row-gap"),
+	SMAP("grid-row-start"),
+	SMAP("grid-template"),
+	SMAP("grid-template-areas"),
+	SMAP("grid-template-columns"),
+	SMAP("grid-template-rows"),
+	SMAP("justify-items"),
+	SMAP("justify-self"),
+	SMAP("row-gap"),
+	SMAP("border-radius"),
+	SMAP("border-bottom-left-radius"),
+	SMAP("border-bottom-right-radius"),
+	SMAP("border-top-left-radius"),
+	SMAP("border-top-right-radius"),
+	SMAP("box-shadow"),
+	SMAP("text-shadow"),
 
 	SMAP("inherit"),
 	SMAP("unset"),
@@ -491,6 +519,12 @@ const stringmap_entry stringmap[LAST_KNOWN] = {
 	SMAP("grid"),
 	SMAP("inline-grid"),
 	SMAP("sticky"),
+	SMAP("dense"),
+	SMAP("span"),
+	SMAP("start"),
+	SMAP("end"),
+	SMAP("self-start"),
+	SMAP("self-end"),
 
 	SMAP("aliceblue"),
 	SMAP("antiquewhite"),
