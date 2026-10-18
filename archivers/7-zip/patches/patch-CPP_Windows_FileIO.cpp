$NetBSD$

IRIX: no d_type in struct dirent (as AIX, Solaris, QNX); no futimens
(the times are set by path after the close); RAM size from sysconf as on
Solaris (no Linux sysinfo).

--- CPP/Windows/FileIO.cpp.orig
+++ CPP/Windows/FileIO.cpp
@@ -1096,7 +1096,13 @@
         FiTime_To_timespec(ATime_defined ? &ATime : NULL, times[0]);
         FiTime_To_timespec(MTime_defined ? &MTime : NULL, times[1]);
         // futimens : POSIX.1-2008
+#ifdef __sgi
+        // IRIX has no futimens: the times stay set, and SetDirTime() below
+        // sets them by path after the close.
+        if (false)
+#else
         if (futimens(_handle, times) == 0)
+#endif
         {
           PRF(printf("\n futimens() OK \n");)
           ATime_defined = false;
