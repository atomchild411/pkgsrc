$NetBSD$

No yywrap: none of the lex libraries is there in a cross build.

--- confparser/conflexer.l.orig
+++ confparser/conflexer.l
@@ -1,3 +1,4 @@
+%option noyywrap
 %{
 /*
  * (c) 2007, Tonnerre Lombard <tonnerre@bsdprojects.net>,
