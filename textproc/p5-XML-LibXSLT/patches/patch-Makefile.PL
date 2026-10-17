$NetBSD$

Cross builds: PERL5_CROSS_SKIP_LINK_TESTS skips have_library's link tests (they\nload a test module into the running perl).

--- Makefile.PL.orig
+++ Makefile.PL
@@ -413,6 +413,12 @@
 
 sub have_library {
     my ($lib, $func) = (@_, "blank");
+    # A cross build cannot load the test module into this perl: trust the
+    # libraries it was given.
+    if ($ENV{PERL5_CROSS_SKIP_LINK_TESTS}) {
+        print "looking for -l$lib... (cross build) yes\n";
+        return 1;
+    }
     if ($func eq "blank")
     {
         printf("looking for -l%s... ", $lib);
