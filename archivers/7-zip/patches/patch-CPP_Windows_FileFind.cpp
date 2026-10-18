$NetBSD$

IRIX: no d_type in struct dirent (as AIX, Solaris, QNX); no futimens
(the times are set by path after the close); RAM size from sysconf as on
Solaris (no Linux sysinfo).

--- CPP/Windows/FileFind.cpp.orig
+++ CPP/Windows/FileFind.cpp
@@ -1321,7 +1321,7 @@
   /* some systems (like CentOS 7.x on XFS) have (Type == DT_UNKNOWN)
      we can call fstatat() for that case, but we use only (Name) check here */
 
-#if !defined(_AIX) && !defined(__sun) && !defined(__QNXNTO__)
+#if !defined(_AIX) && !defined(__sun) && !defined(__QNXNTO__) && !defined(__sgi)
   if (Type != DT_DIR && Type != DT_UNKNOWN)
     return false;
 #endif
@@ -1361,7 +1361,7 @@
 
   fi.iNode = de->d_ino;
   
-#if !defined(_AIX) && !defined(__sun) && !defined(__QNXNTO__)
+#if !defined(_AIX) && !defined(__sun) && !defined(__QNXNTO__) && !defined(__sgi)
   fi.Type = de->d_type;
   /* some systems (like CentOS 7.x on XFS) have (Type == DT_UNKNOWN)
      we can set (Type) from fstatat() in that case.
