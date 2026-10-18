$NetBSD$

IRIX is SVR4 here (clang does not define __SVR4): <dirent.h>, and stat() for file types (no d_type).

--- src/v_src3.c.orig
+++ src/v_src3.c
@@ -36,11 +36,11 @@
 #include <ctype.h>
 #include <errno.h>
 
-#if defined(__CYGWIN32__) || defined(__SVR4)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__sgi)
 #include <sys/stat.h>
 #endif
 
-#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__hpux)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__hpux) || defined(__sgi)
 #include <dirent.h>
 #else
 #include <sys/dir.h>
@@ -4939,7 +4939,7 @@
  char *cp;
  DIR *dp;
  struct dirent *dir;
-#if defined(__CYGWIN32__) || defined(__SVR4)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__sgi)
  struct stat sbuf;
 #endif
   
@@ -4958,7 +4958,7 @@
    if (dir->d_ino == 0) continue;
    if (strcmp(dir->d_name, ".") == 0) continue;
    if (strcmp(dir->d_name, "..") == 0) continue;
-#if defined(__CYGWIN32__) || defined(__SVR4)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__sgi)
    if (stat(dir->d_name, &sbuf) == -1) continue;
    if ((S_IFMT & sbuf.st_mode) == S_IFDIR)
 #else
@@ -4970,7 +4970,7 @@
      else sprintf(dirstr, "%s/%s", path, dir->d_name);
      find_hier(lbep, xfp_hd, bpath, dirstr);
     }
-#if defined(__CYGWIN32__) || defined(__SVR4)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__sgi)
    else if ((S_IFMT & sbuf.st_mode) == S_IFREG)
 #else
    else if (dir->d_type == DT_REG)
@@ -5276,7 +5276,7 @@
  struct xpndfile_t *xfp;
  struct dirent *dir;
  DIR *dp;
-#if defined(__CYGWIN32__) || defined(__SVR4)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__sgi)
  struct stat sbuf;
 #endif
      
@@ -5301,7 +5301,7 @@
      if (dir->d_ino == 0) continue;
      if (strcmp(dir->d_name, ".") == 0) continue;
      /* handle directories */
-#if defined(__CYGWIN32__) || defined(__SVR4)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__sgi)
      if (stat(dir->d_name, &sbuf) == -1) continue;
      if ((S_IFMT & sbuf.st_mode) == S_IFDIR)
 #else
@@ -5328,7 +5328,7 @@
          if (!xfp->wildcard && !xfp->incall) return;
         }
       }
-#if defined(__CYGWIN32__) || defined(__SVR4)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__sgi)
      else if ((S_IFMT & sbuf.st_mode) == S_IFREG)
 #else
      else if (dir->d_type == DT_REG)
@@ -5505,7 +5505,7 @@
  char *cp;
  DIR *dp;
  struct dirent *dir;
-#if defined(__CYGWIN32__) || defined(__SVR4)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__sgi)
  struct stat sbuf;
 #endif
 
@@ -5524,7 +5524,7 @@
    if (dir->d_ino == 0) continue;
    if (strcmp(dir->d_name, ".") == 0) continue;
    if (strcmp(dir->d_name, "..") == 0) continue;
-#if defined(__CYGWIN32__) || defined(__SVR4)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__sgi)
    if (stat(dir->d_name, &sbuf) == -1) continue;
    if ((S_IFMT & sbuf.st_mode) == S_IFDIR)
 #else
@@ -5535,7 +5535,7 @@
      else sprintf(dirstr, "%s/%s", path, dir->d_name);
      expand_single_hier(lbp, lbep, dirstr);
     }
-#if defined(__CYGWIN32__) || defined(__SVR4)
+#if defined(__CYGWIN32__) || defined(__SVR4) || defined(__sgi)
    else if ((S_IFMT & sbuf.st_mode) == S_IFREG)
 #else
    else if (dir->d_type == DT_REG)
