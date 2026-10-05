$NetBSD$

Accept HTML names (attributes such as "@click$lit$"), not only XML names.

--- src/utils/validate.c.orig
+++ src/utils/validate.c
@@ -99,45 +99,25 @@
  */
 bool _dom_validate_name(dom_string *name)
 {
-	uint32_t ch;
-	size_t clen, slen;
-	parserutils_error err;
 	const uint8_t *s;
+	size_t i, slen;
 
-	if (name == NULL)
+	/* HTML's rule, not XML's: names (an attribute's above all) may hold
+	 * anything but white space, quotes, '>', '/', '=' and NUL -- web
+	 * pages and libraries use '@', '$', ':' and the like (Lit's
+	 * "@click$lit$"). */
+	(void) is_first_char;		/* XML's rule, unused now */
+	if (name == NULL || dom_string_length(name) == 0)
 		return false;
-
-	slen = dom_string_length(name);
-	if (slen == 0)
-		return false;
-
 	s = (const uint8_t *) dom_string_data(name);
 	slen = dom_string_byte_length(name);
-	
-	err = parserutils_charset_utf8_to_ucs4(s, slen, &ch, &clen);
-	if (err != PARSERUTILS_OK) {
-		return false;
-	}
-	
-	if (is_first_char(ch) == false)
-		return false;
-	
-	s += clen;
-	slen -= clen;
-	
-	while (slen > 0) {
-		err = parserutils_charset_utf8_to_ucs4(s, slen, &ch, &clen);
-		if (err != PARSERUTILS_OK) {
+	for (i = 0; i < slen; i++) {
+		switch (s[i]) {
+		case '\0': case ' ': case '\t': case '\n': case '\f': case '\r':
+		case '"': case '\'': case '>': case '/': case '=':
 			return false;
 		}
-
-		if (is_name_char(ch) == false)
-			return false;
-
-		s += clen;
-		slen -= clen;
 	}
-
 	return true;
 }
 
