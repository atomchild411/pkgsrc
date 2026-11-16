$NetBSD$

Put the script directory in @INC: Perl 5.26 and later leave out '.', so
Backend.pl could not load its other scripts (Can't locate PlayerInput.pl).

--- src/Backend.cpp.orig
+++ src/Backend.cpp
@@ -163,8 +163,8 @@
 	
 //	char *perl_argv[] = {"", "-d:Trace", "Backend.pl"};
 //	int perl_argc = 3;
-	char *perl_argv[] = {"", "Backend.pl"};
-	int perl_argc = 2;
+	char *perl_argv[] = {"", "-I" DATADIR "/script", "Backend.pl"};
+	int perl_argc = 3;
 	my_perl = perl_alloc();
 	if ( my_perl == NULL )
 	{
