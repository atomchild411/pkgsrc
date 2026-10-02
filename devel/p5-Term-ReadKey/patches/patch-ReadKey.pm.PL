$NetBSD$

Cross builds give blockoptions() in the environment: the module just
built cannot be loaded on the build host.

--- ReadKey.pm.PL.orig	2026-10-02 16:11:08.494885791 +0000
+++ ReadKey.pm.PL	2026-10-02 16:11:08.522886285 +0000
@@ -511,8 +511,14 @@
 require DynaLoader;
 our @ISA = qw(DynaLoader);
 
+# A cross build cannot load the module it has just built: it gives the
+# answer in PKGSRC_READKEY_BLOCKOPTIONS instead.
+if (defined $ENV{PKGSRC_READKEY_BLOCKOPTIONS}) {
+    eval "sub blockoptions { $ENV{PKGSRC_READKEY_BLOCKOPTIONS} }";
+} else {
 print "Bootstrapping the XS for blockoptions: ";
 bootstrap Term::ReadKey or die;
+}
 print blockoptions()."\n";
 
 open OUT, ">>", $file or die "Can't append to $file: $!";
