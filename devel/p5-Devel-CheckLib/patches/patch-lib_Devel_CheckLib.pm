$NetBSD: patch-lib_Devel_CheckLib.pm,v 1.4 2024/04/25 17:56:30 schmonz Exp $

Fix regression reported in https://github.com/mattn/p5-Devel-CheckLib/issues/23.
Keeps p5-Crypt-DH-GMP building on at least NetBSD.
macOS doesn't use -rpath and older linkers don't recognize it.
With PKGSRC_CROSS_NO_EXECUTE set (cross builds), link the test program
but do not run it.

--- lib/Devel/CheckLib.pm.orig	2022-05-04 14:31:10.000000000 +0000
+++ lib/Devel/CheckLib.pm
@@ -295,7 +295,6 @@
 	    $cfile,
 	    (!defined $lib ? () : (
 	      (map "-L$_", @$libpaths),
-	      ($^O eq 'darwin' ? (map { "-Wl,-rpath,$_" } @$libpaths) : ()),
 	      "-l$lib",
 	    )),
 	    @$ld,
@@ -332,7 +331,8 @@
     my @headers = @{$args{header} || []};
     my @incpaths = @{$args{incpath} || []};
     my $analyze_binary = $args{analyze_binary};
-    my $execute = !$args{not_execute};
+    # pkgsrc: a cross build cannot run what it links.
+    my $execute = !$args{not_execute} && !$ENV{PKGSRC_CROSS_NO_EXECUTE};
 
     my @argv = @ARGV;
     push @argv, _parse_line('\s+', 0, $ENV{PERL_MM_OPT}||'');
@@ -454,7 +454,7 @@
         push @Config_ldflags, $config_val if ( $config_val =~ /\S/ );
     }
     my @ccflags = grep { length } _parsewords($Config_ccflags||'', $user_ccflags||'');
-    my @ldflags = grep { length && $_ !~ m/^-Wl/ } _parsewords(@Config_ldflags, $user_ldflags||'');
+    my @ldflags = grep { length } _parsewords(@Config_ldflags, $user_ldflags||'');
     my @paths = split(/$Config{path_sep}/, $ENV{PATH});
     my @cc = _parsewords($Config{cc});
     if (check_compiler ($cc[0], $debug)) {
