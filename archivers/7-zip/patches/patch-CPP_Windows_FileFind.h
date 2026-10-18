$NetBSD$

IRIX: no d_type in struct dirent (as AIX, Solaris, QNX); no futimens
(the times are set by path after the close); RAM size from sysconf as on
Solaris (no Linux sysinfo).

--- CPP/Windows/FileFind.h.orig
+++ CPP/Windows/FileFind.h
@@ -275,13 +275,13 @@
 struct CDirEntry
 {
   ino_t iNode;
-#if !defined(_AIX) && !defined(__sun) && !defined(__QNXNTO__)
+#if !defined(_AIX) && !defined(__sun) && !defined(__QNXNTO__) && !defined(__sgi)
   Byte Type;
 #endif
   FString Name;
 
   /*
-#if !defined(_AIX) && !defined(__sun) && !defined(__QNXNTO__)
+#if !defined(_AIX) && !defined(__sun) && !defined(__QNXNTO__) && !defined(__sgi)
   bool IsDir() const
   {
     // (Type == DT_UNKNOWN) on some systems
@@ -308,7 +308,7 @@
   bool Fill_FileInfo(const CDirEntry &de, CFileInfo &fileInfo, bool followLink) const;
   bool DirEntry_IsDir(const CDirEntry &de, bool followLink) const
   {
-#if !defined(_AIX) && !defined(__sun) && !defined(__QNXNTO__)
+#if !defined(_AIX) && !defined(__sun) && !defined(__QNXNTO__) && !defined(__sgi)
     if (de.Type == DT_DIR)
       return true;
     if (de.Type != DT_UNKNOWN)
