$NetBSD: patch-src_Mixfix_token.cc,v 1.2 2015/12/29 23:34:51 dholland Exp $

Don't use <rope> with clang, but fall back to <string>. Untested for
functionality.
IRIX: use strchr(); index() needs <strings.h>.

--- src/Mixfix/token.cc.orig
+++ src/Mixfix/token.cc
@@ -632,7 +632,7 @@
 	      }
 	  }
 	}
-      result.append(c);
+      result.push_back(c);
       seenBackslash = false;
     }
   CantHappen("bad end to string");
@@ -797,7 +797,7 @@
   const char* name = stringTable.name(codeNr);
   char* s = new char[strlen(name) + 1];
   strcpy(s, name);
-  char* p = index(s, '/');
+  char* p = strchr(s, '/');
   Assert(p != 0, "no /");
   *p = '\0';
   mpz_set_str(numerator.get_mpz_t(), s, 10);
