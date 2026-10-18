$NetBSD$

IRIX: use strchr(); index() needs <strings.h>.

--- src/Mixfix/mixfixParser.cc.orig
+++ src/Mixfix/mixfixParser.cc
@@ -611,7 +611,7 @@
 	const char* name = (*currentSentence)[pos].name();
 	char* s = new char[strlen(name) + 1];
 	strcpy(s, name);
-	char* p = index(s, '/');
+	char* p = strchr(s, '/');
 	Assert(p != 0, "no /");
 	*p = '\0';
 	mpz_class numerator(s, 10);
