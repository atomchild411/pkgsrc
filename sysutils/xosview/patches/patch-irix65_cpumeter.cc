$NetBSD$

endl is in std (no using-directive in this file).

--- irix65/cpumeter.cc.orig
+++ irix65/cpumeter.cc
@@ -18,7 +18,7 @@
             cputime_[i][j] = 0;
 
     if ((sinfosz = sysmp(MP_SASZ, MPSA_SINFO)) < 0) {
-           std::cerr << "sysinfo scall interface not supported" << endl;
+           std::cerr << "sysinfo scall interface not supported" << std::endl;
         parent_->done(1);
         return;
     }
