$NetBSD$

IRIX: pkgsrc editline installs readline/readline.h (as the BSDs have it).

--- dnsdist-console-completion.cc.orig
+++ dnsdist-console-completion.cc
@@ -27,7 +27,7 @@
 #include "dnsdist-rule-chains.hh"
 
 #ifdef HAVE_LIBEDIT
-#if defined(__OpenBSD__) || defined(__NetBSD__)
+#if defined(__OpenBSD__) || defined(__NetBSD__) || defined(__sgi)
 // If this is not undeffed, __attribute__ will be redefined by /usr/include/readline/rlstdc.h
 #undef __STRICT_ANSI__
 #include <readline/readline.h>
